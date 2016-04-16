/* -*- coding: utf-8 -*- */
/* -*- mode: c -*- */
/*
 * Dislocker -- enables to read/write on BitLocker encrypted partitions under
 * Linux
 * Copyright (C) 2012-2013  Romain Coltel, Hervé Schauer Consultants
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */
#ifndef RECOVERY_PASSWORD_H
#define RECOVERY_PASSWORD_H


#include "common.h"
#include "../stretch_key.h"

// Specifications of the recovery password
#define NB_RP_BLOCS   8
#define NB_DIGIT_BLOC 6

#define INTERMEDIATE_KEY_LENGTH 32


/*
 * Prototypes
 */

int is_valid_key(const uint8_t *recovery_password, uint16_t *short_password);

int intermediate_key(const uint8_t *recovery_key, const uint8_t *salt, uint8_t *result_key);

int prompt_rp(uint8_t** rp);

void print_intermediate_key(uint8_t *result_key);


#endif // RECOVERY_PASSWORD_H
