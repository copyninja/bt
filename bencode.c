#include "bencode.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct benc *benc_decode(FILE *in)
{
	if (feof(in))
		perror("%s: %s\n", "benc_decode", strerror(errno));
	else
		return benc_decode_full(in);
}

static unsigned char read_byte(FILE *in)
{
	unsigned char c = fread((unsigned char *)&c, sizeof(unsigned char), 1, in);
	
	if (c != NULL)
		return c;
	else
		perror("%s: %s\n", "read_byte", strerror(errno));
}

static struct benc *benc_decode_full(FILE *in)
{
	unsigned char first = read_byte(in);
	
	switch (first) {
	case 'i':
		return read_number(in, 'e', 0);
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return read_string(in, ':', first - '0');
	case 'l':
		return 0; //TODO
	case 'd':
		return 0; //TODO
	}
}

static struct benc *read_number(FILE *in, char terminator, int accumulator)
{
	unsigned char c;
	int int_val = acc;
	struct benc *b = (struct benc *)malloc(sizeof(struct benc));
	
	c = fread((unsigned char *)&c, sizeof(unsigned char), 1, in);
	while (c != terminator) {
		int_val = int_val * 10 + (c - '0');
	}
	b->type = benc_int;
	b->d.i = int_val;
	
	return b;
}

static struct benc *read_string(FILE *in, char terminator, int accumulator)
{
	struct benc b = (struct benc *)malloc(sizeof(struct benc));
	struct benc blen = read_number(in, terminator, accumulator);
	int len = benc->d.i;
	char *s = (char *)malloc(sizeof(char) * (len + 1));
	
	for (size_t i = 0; i < len; i++)
		s[i] = read_byte(in);
	s[i] = '\0';
	
	b->type = benc_str;
	b->d.s = s;

	return b;	
}

struct benc *benc_decode_list(unsigned char *stream)
{
	// l followed by one or more bencoded values, followed by e.
	int i = 0;
	struct benc *b = (struct benc *)malloc(sizeof(struct benc));
	b->type = benc_list;
	
	assert(stream[i] == 'l');
	while (*stream != 'e') {
		b->l.b = benc_decode(stream)
	}
}