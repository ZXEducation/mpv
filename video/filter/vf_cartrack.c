// /*
//  * This file is part of mpv.
//  *
//  * mpv is free software; you can redistribute it and/or
//  * modify it under the terms of the GNU Lesser General Public
//  * License as published by the Free Software Foundation; either
//  * version 2.1 of the License, or (at your option) any later version.
//  *
//  * mpv is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU Lesser General Public License for more details.
//  *
//  * You should have received a copy of the GNU Lesser General Public
//  * License along with mpv.  If not, see <http://www.gnu.org/licenses/>.
//  */

// #include <inttypes.h>
// #include <math.h>
// #include <stdatomic.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include <libavutil/frame.h>

// #include "common/common.h"
// #include "common/msg.h"
// #include "filters/filter.h"
// #include "filters/filter_internal.h"
// #include "filters/user_filters.h"
// #include "options/m_option.h"
// #include "video/img_format.h"
// #include "video/mp_image.h"
// #include "video/fmt-conversion.h"

// struct priv {};

// #ifdef _WIN32
// #define MPV_EXPORT __declspec(dllexport)
// #elif defined(__GNUC__) || defined(__clang__)
// #define MPV_EXPORT __attribute__((visibility("default")))
// #else
// #define MPV_EXPORT
// #endif

// bool (*mpv_cartrack_process)(AVFrame *, bool) = NULL;
// void (*mpv_cartrack_frame_increment)(void) = NULL;

// MPV_EXPORT void mpv_set_cartrack_process(bool (*func)(AVFrame *, bool)) {
//     mpv_cartrack_process = func;
// }
// MPV_EXPORT void mpv_set_cartrack_frame_increment(void (*func)(void)) {
//     mpv_cartrack_frame_increment = func;
// }

// extern atomic_bool enable_cartrack;
// int decoded_queue_size = 0;
// bool can_track = false;

// static void vf_cartrack_process(struct mp_filter *f) {
//     if (!mp_pin_can_transfer_data(f->ppins[1], f->ppins[0])) return;

//     struct mp_frame frame = mp_pin_out_read(f->ppins[0]);
//     if (mp_frame_is_signaling(frame) || frame.type != MP_FRAME_VIDEO) {
//         mp_pin_in_write(f->ppins[1], frame);
//         return;
//     }

//     struct mp_image *in_img = frame.data;

//     if (decoded_queue_size > 90) {
//         can_track = true;
//     } else if (decoded_queue_size < 30) {
//         can_track = false;
//     }
//     if (can_track && atomic_load(&enable_cartrack) && mpv_cartrack_process != NULL) {
//         AVFrame *frame = mp_image_to_av_frame(in_img);
//         if (frame) {
//             if (mpv_cartrack_process(frame, decoded_queue_size < 60)) {
//                 for (int p = 0; p < MP_MAX_PLANES; p++) {
//                     av_buffer_unref(&in_img->bufs[p]);
//                     in_img->bufs[p] = frame->buf[p];
//                 }
//                 for (int i = 0; i < 4; i++) {
//                     in_img->planes[i] = frame->data[i];
//                     in_img->stride[i] = frame->linesize[i];
//                 }
//                 mp_image_set_size(in_img, frame->width, frame->height);
//                 mp_image_setfmt(in_img, pixfmt2imgfmt(frame->format));
//             }
//         }
//     } else {
//         if (mpv_cartrack_frame_increment != NULL) {
//             mpv_cartrack_frame_increment();
//         }
//     }
//     mp_pin_in_write(f->ppins[1], frame);
// }

// static const struct mp_filter_info vf_cartrack_filter = {
//     .name = "cartrack",
//     .process = vf_cartrack_process,
//     .priv_size = sizeof(struct priv),
// };

// static struct mp_filter *vf_cartrack_create(struct mp_filter *parent, void *options) {
//     struct mp_filter *f = mp_filter_create(parent, &vf_cartrack_filter);
//     if (!f) {
//         talloc_free(options);
//         return NULL;
//     }

//     mp_filter_add_pin(f, MP_PIN_IN, "in");
//     mp_filter_add_pin(f, MP_PIN_OUT, "out");

//     return f;
// }

// const struct mp_user_filter_entry vf_cartrack = {
//     .desc =
//         {
//             .description = "cartrack filter",
//             .name = "cartrack",
//             .priv_size = 0,
//             .priv_defaults = NULL,
//             .options = NULL,
//         },
//     .create = vf_cartrack_create,
// };
