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
#ifndef ENCOMMON_H
#define ENCOMMON_H


#include "common.h"
#include "config.h"
#include "metadata/metadata.h"


#include "polarssl/aes.h"
#include "ssl_bindings.h"


#define AES_CTX_LENGTH 256


/**
 * AES contexts "used" during encryption/decryption
 * @see encryption/decrypt.c
 * @see encryption/encrypt.c
 */
typedef struct _aes_contexts {
	AES_CONTEXT FVEK_E_ctx;
	AES_CONTEXT FVEK_D_ctx;
	
	AES_CONTEXT TWEAK_E_ctx;
	AES_CONTEXT TWEAK_D_ctx; /* useless, never used */
} contexts_t;



/**
 * Structure used for operation on disk (encryption/decryption)
 */
typedef struct _data {
	/* Volume metadata */
	bitlocker_header_t* metadata;
	/* Size of files containing metadata on the NTFS level */
	off_t               metafiles_size;   /* BitLocker's metadata */
	off_t               virtualized_size; /* NTFS backed-up sectors */
	
	/* Extended info which may be present (NULL otherwise) */
	extended_info_t*    xinfo;
	
	/* Where the real partition begins */
	off_t               part_off;
	/* Volume sector size */
	uint16_t            sector_size;
	/* Volume size, in bytes */
	uint64_t            volume_size;
	/* File descriptor to access the volume */
	int                 volume_fd;
	
	/* Contexts used to encrypt or decrypt */
	contexts_t*         ctx;
	
	/* Configuration parameters */
	dis_config_t*       cfg;
	
	/* Function to decrypt a region of the volume */
	int(*decrypt_region)(int fd, size_t nb_read_sector,  uint16_t sector_size, off_t sector_start, uint8_t* output);
	/* Function to encrypt a region of the volume */
	int(*encrypt_region)(int fd, size_t nb_write_sector, uint16_t sector_size, off_t sector_start, uint8_t* input);
	
	/* FUSE uses threads. We need to protect our "lseek/read" and "lseek/write" sequences */
	pthread_mutex_t     mutex_lseek_rw;
} data_t;




/** Data used globally for operation on disk (encryption/decryption) */
UNUSED data_t disk_op_data;




#endif /* ENCOMMON_H */
