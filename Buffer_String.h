/**
 * This file was automatically generated to be a generic Buffer.
 * Buffers are C "arrays" that also bundles the :capacity and :length.
 */

struct Buffer_String
{
	int capacity;
	int length;
	struct String buffer[0];
};

struct Buffer_String* Buffer_String_init(int capacity);

struct Buffer_String* Buffer_String_filter(struct Buffer_String* self, bool (*filter)(struct String));

bool Buffer_String_put(struct Buffer_String* self, int idx, struct String item);

bool Buffer_String_push(struct Buffer_String* self, struct String item);

bool Buffer_String_pop(struct Buffer_String* self);

bool Buffer_String_swap(struct Buffer_String* self, int left_idx, int right_idx);
