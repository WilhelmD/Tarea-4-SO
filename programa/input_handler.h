//
// Created by fchacon on 22-11-16.
//

#include <string.h>

#ifndef PROGRAMA_INPUT_HANDLER_H
#define PROGRAMA_INPUT_HANDLER_H

char **split(char *phrase, const size_t length, const char delimiter, size_t *n_tokens);

char **split_line(char *phrase, size_t *n_tokens);

char *read_char();

char *read_line();

#endif //PROGRAMA_INPUT_HANDLER_H