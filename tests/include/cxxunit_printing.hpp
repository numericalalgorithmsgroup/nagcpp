// clang-format off
/* Simple C++ testing library: code for colorful printing.
 * Copyright: 2014-2017, Dmitry Shachnev.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * original version taken from https://github.com/mitya57/cxxunit
 */

#ifndef CXXUNIT_PRINTING_HPP
#define CXXUNIT_PRINTING_HPP

#if defined (_WIN32) || defined (WIN32)
  #define colorize(color, text, fd) (text)
  #define STDOUT_FILENO 1
  #define STDERR_FILENO 2
#else /* Not WIN32 */

#include <sstream>
#include <string>
#include <unistd.h>

std::string colorize(unsigned short color, std::string const &text, int fd) {
  if (isatty(fd)) {
    std::stringstream stream;
    stream << "\x1b[" << std::hex << (color & 0xff);
    if (color & 0x100) {
      stream << ";01";
    }
    stream << "m" << text << "\x1b[00m";
    std::string result;
    std::getline(stream, result);
    return result;
  }
  return text;
}
#endif /* WIN32 / Not WIN32 */

#define COLOR_DARK_GRAY   0x30
#define COLOR_BLACK      0x130
#define COLOR_RED         0x31
#define COLOR_DARK_RED   0x131
#define COLOR_GREEN       0x32
#define COLOR_DARK_GREEN 0x132
#define COLOR_YELLOW      0x33
#define COLOR_BROWN      0x133
#define COLOR_BLUE        0x34
#define COLOR_DARK_BLUE  0x134
#define COLOR_FUCHSIA     0x35
#define COLOR_PURPLE     0x135
#define COLOR_TEAL        0x36
#define COLOR_TURQUOISE  0x136
#define COLOR_WHITE       0x37
#define COLOR_LIGHT_GRAY 0x137

#define O_INFO(text) colorize(COLOR_DARK_BLUE, text, STDOUT_FILENO)
#define O_ERROR(text) colorize(COLOR_DARK_RED, text, STDOUT_FILENO)
#define O_WARNING(text) colorize(COLOR_BROWN, text, STDOUT_FILENO)
#define O_SUCCESS(text) colorize(COLOR_DARK_GREEN, text, STDOUT_FILENO)

#define E_INFO(text) colorize(COLOR_DARK_BLUE, text, STDERR_FILENO)
#define E_ERROR(text) colorize(COLOR_DARK_RED, text, STDERR_FILENO)
#define E_WARNING(text) colorize(COLOR_BROWN, text, STDERR_FILENO)
#define E_SUCCESS(text) colorize(COLOR_DARK_GREEN, text, STDERR_FILENO)

#endif /* CXXUNIT_PRINTING_HPP */
// clang-format on
