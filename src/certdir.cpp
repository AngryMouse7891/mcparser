#include<string>

std::string get_cert_dir(){
    #if _WIN32
    return "cacert.pem";
    #elif __APPLE__
    return "/System/Library/Keychains/SystemRootCertificates.keychain";
    #else
    return "/etc/ssl/certs/ca-certificates.crt";
    #endif
}