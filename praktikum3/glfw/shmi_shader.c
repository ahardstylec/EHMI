#include "shmi_shader.h"
#include <stdio.h>
#include <stdlib.h>

char *shmi_shader_load(char *shader_file_name) {
  FILE *shader_file = fopen(shader_file_name, "ro");
  if (!shader_file)
    perror(shader_file_name), exit(1);

  // get file size
  fseek(shader_file, 0L, SEEK_END);
  size_t file_size = ftell(shader_file);
  rewind(shader_file);

  char *read_buffer = malloc(file_size + 1);
  if (!read_buffer)
    fclose(shader_file), fputs("malloc error", stderr), exit(1);

  if (1 != fread(read_buffer, file_size, 1, shader_file))
    fclose(shader_file), free(read_buffer), fputs("entire read fails", stderr),
        exit(1);

  return read_buffer;
}


void shmi_shader_cleanup()
{

}
