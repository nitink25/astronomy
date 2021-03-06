/*=============================================================================
Copyright 2020 Gopi Krishna Menon <krishnagopi487.github@outlook.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_TEST_MODULE binary_table_test

#include <boost/astronomy/io/binary_table.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/astronomy/io/fits_stream.hpp>
#include <boost/astronomy/io/default_card_policy.hpp>
#include <boost/astronomy/io/binary_data_converter.hpp>
#include "base_fixture.hpp"

using namespace boost::astronomy::io;

namespace fits_test {

    class binary_table_fixture :public base_fixture<fits_stream,card_policy> {
    public:
        basic_binary_table_extension<card_policy,binary_data_converter> binary_table1;
        binary_table_fixture() {
#ifdef SOURCE_DIR
            samples_directory = std::string((std::string(SOURCE_DIR) +
                "/fits_sample_files/"));
#else
            samples_directory = std::string(
                std::string(boost::unit_test::framework::master_test_suite().argv[1]) +
                "/fits_sample_files/");
#endif
            load_file("fits_sample3.fits");
            initialize_binary_table_hdu(binary_table1, "fits_sample3");       
        }
    private:

        void initialize_binary_table_hdu(basic_binary_table_extension<card_policy, binary_data_converter>& binary_table_hdu, const std::string& sample_name) {
            hdu_store<card_policy>* raw_binary_table_sample = get_raw_hdu(sample_name, "BINTABLE");
            if (raw_binary_table_sample != nullptr) {
                binary_table_hdu = basic_binary_table_extension<card_policy, binary_data_converter>(raw_binary_table_sample->hdu_header, raw_binary_table_sample->hdu_data_buffer);
            }
        }
    };
}



BOOST_AUTO_TEST_SUITE(convenience_methods)

BOOST_FIXTURE_TEST_CASE(binary_table_get_data, fits_test::binary_table_fixture) {
    BOOST_REQUIRE_EQUAL(binary_table1.get_data().size(), 1);

}

BOOST_FIXTURE_TEST_CASE(binary_table_set_data, fits_test::binary_table_fixture) {
    fits_test::hdu_store<card_policy>* raw_bin_hdu = get_raw_hdu("fits_sample3", "BINTABLE");
    basic_binary_table_extension<card_policy, binary_data_converter> test_hdu(raw_bin_hdu->hdu_header,"");

    test_hdu.set_data(raw_bin_hdu->hdu_data_buffer);

    BOOST_REQUIRE_EQUAL(test_hdu.get_data().size(), 1);

    auto del_time_col = test_hdu.get_column<std::vector<boost::float32_t>>("DEL_TIME");
    std::vector<boost::float32_t> row1_dat = del_time_col[0];
    BOOST_REQUIRE_CLOSE(row1_dat[119], 595.0, 0.001);
}

BOOST_AUTO_TEST_CASE(binary_table_check_column_size) {
    auto col_size = basic_binary_table_extension<card_policy, binary_data_converter>::column_size("144000I");
    BOOST_REQUIRE_EQUAL(col_size, 288000);
}

BOOST_FIXTURE_TEST_CASE(binary_table_get_column, fits_test::binary_table_fixture) {
    auto column_info =binary_table1.get_column<std::vector<boost::float32_t>>("DEL_TIME");
    std::vector<boost::float32_t> row1_dat = column_info[0];

    BOOST_REQUIRE_CLOSE(row1_dat[119], 595.0, 0.001);
}

BOOST_AUTO_TEST_CASE(binary_table_check_element_count) {
    auto element_count = basic_binary_table_extension<card_policy, binary_data_converter>::element_count("300I");
    BOOST_REQUIRE_EQUAL(element_count, 300);
    
}
BOOST_AUTO_TEST_CASE(binary_table_check_element_count_with_no_number) {
    auto element_count = basic_binary_table_extension<card_policy, binary_data_converter>::element_count("I");
    BOOST_REQUIRE_EQUAL(element_count, 1);
}
BOOST_AUTO_TEST_CASE(binary_table_get_type) {
    auto type = basic_binary_table_extension<card_policy, binary_data_converter>::get_type("242000I");
    BOOST_REQUIRE_EQUAL(type, 'I');
}

BOOST_AUTO_TEST_CASE(binary_table_type_size) {
    auto type_size = basic_binary_table_extension<card_policy, binary_data_converter>::type_size('A');
    BOOST_REQUIRE_EQUAL(type_size, 1);
 
}
BOOST_AUTO_TEST_CASE(binary_table_type_size_invalid_type) {

    BOOST_REQUIRE_THROW((basic_binary_table_extension<card_policy,binary_data_converter>::type_size('G')), boost::astronomy::invalid_table_colum_format);
}

BOOST_AUTO_TEST_SUITE_END()
