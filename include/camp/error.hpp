

#ifndef CAMP_ERROR_HPP
#define CAMP_ERROR_HPP


#include <camp/config.hpp>
#include <cstdlib>
#include <exception>


namespace camp
{
/**
 * \brief Base class for every exception thrown in CAMP
 */
class CAMP_API Error : public std::exception
{
public:

    /**
     * \brief Destructor
     */
    virtual ~Error() throw();

    /**
     * \brief Return a description of the error
     *
     * \return Pointer to a string containing the error message
     */
    virtual const char* what() const throw();

    /**
     * \brief Get the source file where the exception was thrown
     *
     * \return Pointer to a string containing the source filename
     */
    const char* file() const throw();

    /**
     * \brief Get the line number in the source file where the exception was thrown
     *
     * \return Line number
     */
    int line() const throw();

    /**
     * \brief Set the source file and the line number where the exception was thrown
     *
     * This function is meant for internal use only
     *
     * \param file Source filename
     * \param line Line number in the source file
     */
    void setContext(const char* file, int line) throw();

protected:

    /**
     * \brief Default constructor
     */
    Error();

private:

    char m_file[256]; ///< Source filename where the error was thrown
    int m_line; ///< Line number in the source file where the error was thrown
};

namespace detail
{
/**
 * \brief Setup a CAMP error with the current context
 *
 * \param error Error to setup (note: the returned error is a copy of the source error)
 * \param file Source filename
 * \param line Line number in the source file
 *
 * \return Copy of \a error setup with the current context
 */
template <typename T>
T setupError(T error, const char* file, int line)
{
    error.setContext(file, line);
    return error;
}

} // namespace detail

} // namespace camp

/**
 * \brief Trigger a CAMP error
 */
#define CAMP_ERROR(error) throw camp::detail::setupError(error, __FILE__, __LINE__)


#endif // CAMP_ERROR_HPP
