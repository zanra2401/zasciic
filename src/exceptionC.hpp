#pragma once
#include <string>
#include <exception>

class NotFoundException : public std::exception {
  private:
    std::string value;
    const char* message;
  public:
    NotFoundException(const std::string &val);

    const char* what() const noexcept override;

    std::string getValue() const;
};


class ImageErrorException : public std::exception {
  private:
    const unsigned char *value;
    const char* message;
  public:
    ImageErrorException(const unsigned char *&val);

    const char* what() const noexcept override;

    const unsigned char* getValue() const;
};

class NotSupportedException : public std::exception {
  private:
    const char* message;
  public:
    NotSupportedException(const char *message);
    const char* what() const noexcept override;
};
