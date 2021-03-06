/*=============================================================================
Copyright 2018 Pranam Lashkari <plashkari628@gmail.com>
Copyright 2019 blisterz009     <33365962+blisterz009@users.noreply.github.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP
#define BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP

#include <exception>
#include <string>

namespace boost
{
    namespace astronomy
    {
        class fits_exception : public std::exception
        {
        public:
            const char* what() const throw()
            {
                return "FITS exception";
            }
        };

        class wrong_extension_type :public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "wrong extension type";
            }
        };

        class invalid_card : public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "The given Card String does not follow all the requirements of a Card";
            }
        };

        class invalid_cast : public fits_exception
        {
            std::string message;
        public:
            invalid_cast(const std::string& error_message) :message(error_message) {}
            const char* what() const throw()
            {
                return message.c_str();
            }
        };


        // ? What is this???
        class hdu_unit_overflow_exception : public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "HDU unit can accommodate max 36 cards";
            }
        };

        class invalid_key_length_exception : public invalid_card
        {
        public:
            const char* what() const throw()
            {
                return "Key length must not be more than 8 chars";
            }
        };

        class invalid_value_length_exception : public invalid_card
        {
        public:
            const char* what() const throw()
            {
                return "Value length must not be more than 70 chars including comments";
            }
        };

        class key_not_defined_exception : public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "Key is not defined";
            }
        };

        class invalid_table_colum_format : public fits_exception
        {
        public:
            const char* what() const throw()
            {
                return "invalid_table_colum_format";
            }
        };
        class file_reading_exception : public fits_exception {
            std::string message;
        public:
            file_reading_exception(const std::string& error_message):message(error_message) {}
            const char* what() const noexcept override {
                return message.c_str();
            }

        };
        class column_not_found_exception : public fits_exception {
            std::string message;
        public:
            column_not_found_exception(const std::string& column_name) {
                message = "Could not find Column : " + column_name;
            }
            const char* what() const noexcept override {
                return message.c_str();
            }

        };

        class column_exception :public fits_exception {
        public:
            const char* what() const noexcept override {
                return "Column operation failed";
            }
        };


    } //namespace astronomy
} //namespace boost
#endif // !BOOST_ASTRONOMY_EXCEPTION_FITS_EXCEPTION_HPP

