/*
 * Copyright (C) 2017 Advanced Driver Information Technology Joint Venture GmbH
 * Copyright © 2020 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <libweston/libweston.h>

#include "plugin.h"
#include "transmitter_api.h"

void
transmitter_output_destroy(struct weston_transmitter_output *output)
{
	wl_list_remove(&output->link);
	free(output);
}

int
transmitter_remote_create_output_with_name(struct weston_transmitter_remote *remote, char *name)
{
	struct weston_transmitter_output *output;

	output = zalloc(sizeof(*output));
	if (!output)
		return -1;

	output->remote = remote;
	output->name = name;
	wl_list_insert(&remote->output_list, &output->link);

	return 0;
}
