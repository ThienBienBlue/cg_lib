#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "./String.h"
#include "./Buffer_String.h"

struct Buffer_String* Buffer_String_init(int capacity)
{
	if (capacity < 0)
	{
		capacity = 0;
	}

	struct Buffer_String* retval = (struct Buffer_String*)malloc(sizeof(struct Buffer_String) + capacity * sizeof(struct String));

	if (retval != NULL)
	{
		retval->capacity = capacity;
		retval->length = 0;
	}

	return retval;
}

struct Buffer_String* Buffer_String_filter(struct Buffer_String* self, bool (*filter)(struct String))
{
	int capacity = self->capacity;
	struct String* buffer = self->buffer;
	struct Buffer_String* retval = Buffer_String_init(capacity);

	for (int idx = 0; idx < capacity; idx++)
	{
		struct String item = buffer[idx];

		if (filter(item))
		{
			Buffer_String_push(retval, item);
		}
	}

	return retval;
}

bool Buffer_String_put(struct Buffer_String* self, int idx, struct String item)
{
	if (self != NULL && idx < self->capacity)
	{
		// Assignment won't compile if struct String has const fields.
		struct String* write = self->buffer + idx;
		void* written = memmove(write, &item, sizeof(struct String));

		if (written != NULL && self->length <= idx)
		{
			self->length = idx + 1;
		}

		return written != NULL;
	}
	else
	{
		return false;
	}
}

bool Buffer_String_push(struct Buffer_String* self, struct String item)
{
	if (self != NULL)
	{
		return Buffer_String_put(self, self->length, item);
	}
	else
	{
		return false;
	}
}

bool Buffer_String_pop(struct Buffer_String* self)
{
	if (self == NULL || self->length <= 0)
	{
		return false;
	}

	self->length--;

	return true;
}

bool Buffer_String_swap(struct Buffer_String* self, int left_idx, int right_idx)
{
	if (self == NULL)
	{
		return false;
	}

	int len = self->length;
	struct String* buffer = self->buffer;

	if (left_idx < 0 || len <= left_idx || right_idx < 0 || len <= right_idx)
	{
		return false;
	}

	struct String left = buffer[left_idx];
	struct String right = buffer[right_idx];

	bool left_written = Buffer_String_put(self, right_idx, left);
	bool right_written = Buffer_String_put(self, left_idx, right);

	return left_written && right_written;
}
