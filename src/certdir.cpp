#include<string>
#include <sys/stat.h>

int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0); // 如果文件存在，stat 返回 0
}

std::string linux_cert_dir(){
    if (file_exists("/etc/ssl/certs/ca-certificates.crt"))
    {
        return "/etc/ssl/certs/ca-certificates.crt";
    }
    else
    {
        return "/etc/ssl/ca-bundle.pem";
    }
    
}

std::string get_cert_dir(){
    #if _WIN32
    return "cacert.pem";
    #elif __APPLE__
    return "/System/Library/Keychains/SystemRootCertificates.keychain";
    #else
    return linux_cert_dir();
    #endif
}