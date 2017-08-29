/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license in the file COPYING
 * or http://www.opensource.org/licenses/CDDL-1.0.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file COPYING.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2017 Saso Kiselkov. All rights reserved.
 */

#ifndef	_ACF_UTILS_WAV_H_
#define	_ACF_UTILS_WAV_H_

#include <stdint.h>
#include <al.h>

#include "geom.h"
#include "types.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct alc alc_t;

typedef struct wav_fmt_hdr {
	uint16_t	datafmt;	/* PCM = 1 */
	uint16_t	n_channels;
	uint32_t	srate;		/* sample rate in Hz */
	uint32_t	byte_rate;	/* (srate * bps * #channels) / 8 */
	uint16_t	padding;	/* unused */
	uint16_t	bps;		/* bits per sample */
} wav_fmt_hdr_t;

typedef struct wav_s {
	char		*name;
	wav_fmt_hdr_t	fmt;
	double		duration;	/* in seconds */
	alc_t		*alc;
	ALuint		albuf;
	ALuint		alsrc;
} wav_t;

char **openal_list_output_devs(size_t *num_p);
alc_t *openal_init(const char *devname, bool_t shared);
void openal_fini(alc_t *alc);

wav_t *wav_load(const char *filename, const char *descr_name, alc_t *alc);
void wav_free(wav_t *wav);

void wav_set_gain(wav_t *wav, float gain);
void wav_set_loop(wav_t *wav, bool_t loop);
void wav_set_pitch(wav_t *wav, float pitch);
void wav_set_position(wav_t *wav, vect3_t pos);

bool_t wav_play(wav_t *wav);
void wav_stop(wav_t *wav);

#ifdef	__cplusplus
}
#endif

#endif	/* _ACF_UTILS_WAV_H_ */
