#include "exceptionC.hpp"
#include <string>


// NotFoundException
NotFoundException::NotFoundException(const std::string &val) : value(val) {
  message = "File Not Fond";
}

const char* NotFoundException::what() const noexcept {
  return message;
}

std::string NotFoundException::getValue() const {
  return value;
}

// ImageErrorException
ImageErrorException::ImageErrorException(const unsigned char *&val) : value(val) {
  message = "Image Error";
}

const char* ImageErrorException::what() const noexcept {
  return message;
}

const unsigned char* ImageErrorException::getValue() const {
  return value;
}

// NotSupportedException
NotSupportedException::NotSupportedException(const char *message) {
  message = message;
}

const char* NotSupportedException::what() const noexcept {
  return message;
}
