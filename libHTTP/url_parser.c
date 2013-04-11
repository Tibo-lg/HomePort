// url_parser.c

/*  Copyright 2013 Aalborg University. All rights reserved.
*   
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*  
*  1. Redistributions of source code must retain the above copyright
*  notice, this list of conditions and the following disclaimer.
*  
*  2. Redistributions in binary form must reproduce the above copyright
*  notice, this list of conditions and the following disclaimer in the
*  documentation and/or other materials provided with the distribution.
*  
*  THIS SOFTWARE IS PROVIDED BY Aalborg University ''AS IS'' AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Aalborg University OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
*  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
*  SUCH DAMAGE.
*  
*  The views and conclusions contained in the software and
*  documentation are those of the authors and should not be interpreted
*  as representing official policies, either expressed.
*/

#include <string.h>
#include <stdlib.h>

#include "url_parser.h"

struct url_parser_instance {
	struct url_parser_settings *settings;

	int state;
	unsigned int last_parsed_pos;
	unsigned buffer_size;
	char* buffer;
};

struct url_parser_instance *up_create(struct url_parser_settings *settings)
{
	struct url_parser_instance *instance;

	instance = malloc(sizeof(struct url_parser_instance));

	instance -> settings = malloc(sizeof(struct url_parser_settings));
	memcpy(instance->settings, settings, sizeof(struct url_parser_settings));

	instance -> state = 0;
	instance -> buffer_size = 0;
	instance -> last_parsed_pos = 0;

	return instance;
}

void up_destroy(struct url_parser_instance *instance)
{
	free(instance->settings);

	if(instance->buffer) {
		free(instance->buffer);
	}
	
	free(instance);
}

void up_add_chunk(struct url_parser_instance *instance, char* chunk, int chunk_size) {
	// Increase the current buffer
	int old_buffer_size = instance->buffer_size;
	instance->buffer_size += chunk_size;
	instance->buffer = realloc(instance->buffer, instance->buffer_size * (sizeof(char)));
	memcpy(instance->buffer+old_buffer_size, chunk, chunk_size);

	// Parse the new chunk in buffer from last_parsed_pos to buffer_size
	unsigned int i;
	for(i = instance->last_parsed_pos; i < instance->buffer_size; i++)
	{
		char c = instance->buffer[i];

		

		instance->last_parsed_pos++;
	}
}

void up_complete(struct url_parser_instance *instance)
{
	if(instance->settings->on_complete != NULL && instance->buffer != NULL) {
		instance->settings->on_complete(instance->buffer);
	}
}
