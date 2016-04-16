.\"                                      Hey, EMACS: -*- nroff -*-
.\" (C) Copyright 2012-2016  Romain Coltel, Hervé Schauer Consultants,
.\"
.\" First parameter, NAME, should be all caps
.\" Second parameter, SECTION, should be 1-8, maybe w/ subsection
.\" other parameters are allowed: see man(7), man(1)
.TH DISLOCKER 1 2016 "Linux" "DISLOCKER"
.\" Please adjust this date whenever revising the manpage.
.\"
.\" Some roff macros, for reference:
.\" .nh        disable hyphenation
.\" .hy        enable hyphenation
.\" .ad l      left justify
.\" .ad b      justify to both left and right margins
.\" .nf        disable filling
.\" .fi        enable filling
.\" .br        insert line break
.\" .sp <n>    insert n+1 empty lines
.\" for manpage-specific macros, see man(7)
.SH NAME
Dislocker file - Read BitLocker encrypted volumes under Linux, OSX and FreeBSD.
.SH SYNOPSIS
dislocker-file [-hqrsv] [-l \fILOG_FILE\fR] [-o \fIOFFSET\fR] [-V \fIVOLUME\fR \fIDECRYPTMETHOD\fR -F[\fIN\fR]] [--] \fINTFS_FILE\fR

Where DECRYPTMETHOD = {-p[\fIRECOVERY_PASSWORD\fR] | -f \fIBEK_FILE\fR | -u[\fIUSER_PASSWORD\fR] | -k \fIFVEK_FILE\fR | -c}
.SH DESCRIPTION
Given a decryption mean, the program is used to decrypt BitLocker encrypted volumes.

This process may take a very long time, depending on the initial volume size, as the program will decrypt the encrypted partition linearly. About this size, note that the created NTFS file will be of the same size as the BitLocker encrypted partition, so you may want to check that you have enough free space on the volume where you put the NTFS file.

This NTFS file won't have any link with the original BitLocker encrypted partition, so you may modify it to suit your needs.
.SH OPTIONS
For program's options description, see dislocker-fuse(1). The only change in the command line is the last argument, which in this case is the \fINTFS_FILE\fR argument:
.PP
.TB
.B NTFS_FILE
the newly created file where NTFS data will be put to, once decrypted from the BitLocker encrypted volume.
.SH EXAMPLES
These are exemples you can run directly.

Dislock the BitLocker encrypted volume:
.IP
.B % dislocker -V /dev/sda2 -p563200-557084-108284-218900-019151-415437-694144-239976 -- decrypted.ntfs
.IP
This will decrypt \fB/dev/sda2\fR into \fBdecrypted.ntfs\fR using the recovery password method.
.TP
To mount the partition once decrypted, use this sort of line:
.B % mount -o loop decrypted.ntfs /mnt/clear
.P
--
.TP
You may have to unmount the NTFS partition before halting the system. In order to do so, you may run this command (replacing your mount point):
.B % umount /mnt/clear
.P
--

Note that these are \fBexamples\fR and, as such, you may need to modify the given command lines. For example, you may want to change the decryption method used in them.
.SH AUTHOR
This tool is developped by Romain Coltel on behalf of HSC (\fBhttp://www.hsc.fr/\fR)
.PP
Feel free to send bugs report to <dislocker __AT__ hsc __DOT__ fr>
