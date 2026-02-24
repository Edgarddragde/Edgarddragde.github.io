#include <stdio.h>
#include <string.h>

void edit_line(char* buffer, int curr_line) {
  for (int i = 0; i < curr_line; i++) {
    buffer = strchr(buffer, '\n') + 1; //bc strchr returns ptr where \n is at
  }

  char* line_end = strchr(buffer, '\n');
  char saved[1024] = {0};
  strcpy(saved, line_end);
  scanf("%s", buffer);
  strcpy(buffer + strlen(buffer), saved);
}
int main(int argc, char** argv) {
  if (argc != 2) return -1;
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return -1;
  }
  char user_input;
  scanf("%c", &user_input);
  printf("%c", user_input);
  if (user_input == 127 || user_input == 8) return 1;

  char buffer[1024] = {0};
  int current_line = 0;
  if (fread(buffer, 1024, 1, f) < 0) {
    perror("fread issue");
    return -1;
  }
  fclose(f);
  printf("Contents:\n%s\n", buffer);
  scanf("%d", &current_line);
  edit_line(buffer, current_line);
  f = fopen(argv[1], "w");
  if (f == NULL) return -1;
  if (fwrite(buffer, strlen(buffer), 1, f) < 0) {
    perror("fwrite issue");
    return -1;
  }
  fclose(f);

}

