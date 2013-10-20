/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_ERRORS_ERROR_HPP
#define QUIRINUS_CORE_ERRORS_ERROR_HPP
namespace quirinus {


class Error: public std::runtime_error
{
public:
  virtual ~Error() throw()
  {}

  Error()
  : std::runtime_error("")
  {}


  // Mesaage functions
  virtual const char*
  what() const throw() = 0;
};


} // namespace quirinus
#endif // QUIRINUS_CORE_ERRORS_ERROR_HPP
