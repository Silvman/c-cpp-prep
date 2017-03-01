#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 256

typedef struct wordlist {
  char *word;
  unsigned n_total; // кол-во повторений
  unsigned last_ind; // последний абзац
  struct wordlist *next; // список односвязный;
} list;

void seekWord(list* current, const unsigned ind, const char* n_word);
void deallocList(list *current);
void printList(const unsigned n, const list *current);
// void printString(const char *str);
  
list* findMeWords(FILE *fp);


// 44 Ломачев, осн. группа, 15 вариант, PREP-12 
int main(const int argc, const char **argv) {
  if (argc != 3) {
    printf("Arguments invalid\n");
    return 1;
  }

  const unsigned c_min_incl = atoi(argv[1]);
  const char *filename = argv[2];
   
  //printf("%d, %s", c_min_incl, filename);
  FILE *document = fopen(filename, "r");

  if (!document) {
    printf("No such file exsists.\n");
    return 1;
  }
  
  list *first = findMeWords(document);
  
  printList(c_min_incl, first);

  deallocList(first);
  fclose(document);
  
  return 0;
}



void seekWord(list* current, const unsigned ind, const char* n_word) {
  int len = strlen(n_word);
  
  // сравнение
  // первого
  if( !strncmp(current->word, n_word, len) ) {
    if(current->last_ind != ind) {
      current->n_total++;
      current->last_ind = ind;

      return;
    }
  }
  // последующих
    while (current->next) {
      current = current->next;

      if( !strncmp(current->word, n_word, len) ) {
	if(current->last_ind != ind) {
	  current->n_total++;
	  current->last_ind = ind;

	  return;
	}
      } 
    }


  // добавление нового

  list *new = (list *)malloc(sizeof(list));
  current->next = new;

  
  new->word = (char *)malloc(sizeof(char) * (len + 1));
  strncpy(new->word, n_word, len);

  new->n_total = 1; // Всего одно вхождение, очевидно
  new->last_ind = ind;
  new->next = NULL;

  return;
}

list* findMeWords(FILE *fp) {
  int n = 1; // счетчик абзацев
  char c;
  int j = 0;
  list* first_word = NULL;
  
  while(j != EOF) { // 
    c = '0';
    // уровень абзаца
    while(c != '\n') {
      
      // уровень слова
      int i = 0;
      char word_buf[MAX_WORD_LENGTH] = {0};
      c = (char)fgetc(fp);
      
      while(!ispunct(c) && !isspace(c)) {
	word_buf[i] = c;
	i++;
	if(i == MAX_WORD_LENGTH - 1) break; // предполагаем что слова не могут быть больше MAX_WORD_LENGTH
	
	c = (char)fgetc(fp);
      }
      
      word_buf[i] = '\0'; // конец слова

      //при отсутствии первого элемента
      if(i != 0) {
	if(first_word == NULL) {
	  first_word = (list*)malloc(sizeof(list));
	  
	  int len = strlen(word_buf);
	  first_word->word = (char *)malloc(sizeof(char) * (len + 1));
	  strncpy(first_word->word, word_buf, len);
	  
	  first_word->n_total = 1; // Всего одно вхождение, очевидно
	  first_word->last_ind = n;
	  first_word->next = NULL;
	  
	  continue;
	} else {
	  seekWord(first_word, n, word_buf);
	}
      }

      // O_O
      j = (int)c;
      if(j == EOF) break;
    }
    
    n++;
  }

  return first_word;
}

void deallocList(list *current) {
  list *further;
  while (current) {
    further = current->next;
    free(current->word);
    free(current);
    current = further;
  }

  return;
}

void printList(const unsigned n, const list *current) {
  if (current == NULL) { printf("Empty list\n"); return; }
  
  /* while (current) {
    if(current->n_total > n) {
      printString(current->word);
      printf(": %d matches\n", current->n_total);
    }

    
    current = current->next;
    } */

  while (current) {
    if(current->n_total > n)
      printf("%22s:\t %d\n", current->word, current->n_total);

    current = current->next;
  }
  
  return;
}

/*
void printString(const char *str) {
  for (int i = 0; str[i] != '\0'; i++)
    printf("%c", str[i]);
  
  return;
}
*/
