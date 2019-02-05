#ifndef _SET_H_
#define _SET_H_

template<typename T>
class set {
private:
  class element {
    private:
      // Структура данных - бинарное дерево; хранимые данные сами являются ключами и для них определена операция <
      T key;

      element* l;
      element* r;

      // Не явл. констатнтным, так как найденный элемент может быть впоследствие изменен (см element::insert)
      element& seekByKey(const T& a) {
        // указатели используется для того, чтобы легко организовать поиск в бесконечном цикле
        // можно через рекурсию и без указателей, но это более затратно по памяти и здесь излишне
        // т.к. не требуется возврат на итерацию выше
        element* buf = this;

        while (1) {
          if (buf->key == a) break;
          if (buf->key < a) {
            if (buf->r) {
              buf = buf->r;
            } else {
              break;
            }
          } else {
            if (buf->l) {
              buf = buf->l;
            } else {
              break;
            }
          }
        }

        return *buf;
      }

      // Аналог верхнего, используется в методе element::find, для работы с константными элементами
      const element& seekByKey(const T& a) const {
        const element* buf = this;

        while (1) {
          if (buf->key == a) break;
          if (buf->key < a) {
            if (buf->r) {
              buf = buf->r;
            } else {
              break;
            }
          } else {
            if (buf->l) {
              buf = buf->l;
            } else {
              break;
            }
          }
        }

        return *buf;
      }

      // Используется в element::erase для поиска наименьшего ключа в правом поддереве
      const T& getMinKey(){
        element* current = this;

        while (current->l)
          current = current->l;

        return current->key;
      }

      // это в private, т.к. используется только в element::erase && нельзя менять элементы вручную
      element& operator = (const element& from){
        key = from.key;
        l = from.l;
        r = from.r;

        return *this;
      }

    public:
      element(const T& a)
        : key(a),
          l(nullptr), r(nullptr) { }

      element(const element& from)
          : key(from.key),
            l(nullptr), r(nullptr) {
        // std::out << "CConstr" << std::endl;
        if (from.l) {
          l = new element(*from.l);
        }

        if (from.r) {
          r = new element(*from.r);
        }
      }

      ~element() {
        if (l) {
          delete l;
        }

        if (r) {
          delete r;
        }
      }

      const element& insert(const T& a, bool& flag) {
        element& buf = this->seekByKey(a);

        if (buf.key != a) {
          flag = true;
          try {
            if(buf.key < a) {
              buf.r = new element(a);
              return *buf.r;
            } else {
              buf.l = new element(a);
              return *buf.l;
            }
          } catch(std::bad_alloc& ba) {
            flag = false;
            throw;
          }
        }

        flag = false;
        return buf;
      }

      // Здесь используется указатель, т.к. удаление можно реализовать только с его применением
      // из-за особенности структуры данных
      element* erase(const T& a){
        element* target = nullptr;

        // в этих двух if - поиск элемента, требующего удаления
        if (a > key && r)	{
      		target = r->erase(a);
      		if (target == r)
      			r = nullptr; // чтобы убрать указатель на удаляемый элемент
      	}

      	if (a < key && l)	{
      		target = l->erase(a);
      		if (target == l)
      			l = nullptr;
      	}

      	if (key == a) {
          // нет потомков - нет проблем
      		if (!l && !r)
             target = this;

          // если есть один потомок, меняем местами данные в потомке и данном элементе
          // и удаляем данный
      		if (l && !r) {
      			target = l;
      			*this = *l;
      		}

      		if (!l && r) {
      			target = r;
      			*this = *r;
      		}

          // если два потомка - меняем ключ этого элемента на самый малый в правом поддереве
          // и удаляем его из правого поддерева
      		if (l && r)	{
            const T& min_key_r = r->getMinKey();

            key = min_key_r;
      			target = r->erase(min_key_r);

          	if (target == r)
          		r = nullptr; // тоже, удаляем указатель на удаляемый элемент
      		}
      	}

      	if (target) {
      	  target->l = nullptr; // чтобы не удалилось лишнего
      		target->r = nullptr;
      	}

      	return target;
      }

      const element& find(const T& a) const{
        const element& closest = this->seekByKey(a);

        if (closest.key == a) {
          return closest;
        } else {
          throw std::invalid_argument("Can't find such number");
        }
      }

      void printAll() const {
        if (l)
          l->printAll();

        std::cout << key << " | ";

        if (r)
          r->printAll();
      }

      // добавил этот оператор, чтобы с возвращаемыми element& можно было работать, как с итератором...
      const T& operator * () const {
        return key;
      }
  };

  element* head;

  int total;

public:
  set() : head(nullptr), total(0) { }

  set(const set& from){
    head = new element(*from.head);
  }

  ~set() {
    if (head)
      delete head;
  }

  const element& insert(const T& a) {
    if (head) {
      bool isInserted;
      const element& buf = head->insert(a, isInserted);

      if (isInserted)
        total++;

      return buf;
    } else {
      try {
        head = new element(a);
        total++;
        return *head;
      } catch(std::bad_alloc& ba) {
        throw;
      }
    }
  }

  const element& find(const T& a) const {
    if (head) {
      return head->find(a);
    }
  }

  bool erase(const T& a){
    if (head) {
      if(element* target = head->erase(a)) {
        delete target;
        total--;
        if (target == head)
          head = nullptr;

        return true;
      }
    }

    return false;
  }

  bool empty() const {
    return (!head ? true : false);
  }

  int size() const {
    return total;
  }

  bool clear() {
    if(head) {
      delete head;
      head = nullptr;
      total = 0;
      return true;
    } else {
      return false;
    }
  }

  void print() {
    std::cout << "| ";
    head->printAll();
    std::cout << std::endl;
    return;
  }
};

#endif // _SET_H_
