#ifndef CERTDIR_H
#define CERTDIR_H

#include<string>
#include<sys/stat.h>

int file_exists(const char *filename);

std::string linux_cert_dir();

std::string get_cert_dir();

#endif