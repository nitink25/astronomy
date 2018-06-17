#ifndef BOOST_ASTRONOMY_COORDINATE_BASE_DIFFERENTIAL_HPP
#define BOOST_ASTRONOMY_COORDINATE_BASE_DIFFERENTIAL_HPP

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/static_assert.hpp>

#include <boost/is_base_template_of.hpp>

namespace boost
{
    namespace astronomy
    {
        namespace coordinate
        {
            typedef boost::geometry::degree degree;
            typedef boost::geometry::radian radian;

            // structure which is the base for all the representation 
            template <int DimensionCount, typename Type>
            struct base_differential
            {
            protected:
                boost::geometry::model::point<double, DimensionCount, Type> diff;

            public:
                // returns the unit vector of current differential
                template <typename ReturnType>
                ReturnType unit_vector() const
                {
                    /*given coordinates/vectors are converted into cartesian and
                    unit vector of it is returned by converting it into requested type*/

                    /*checking return type if they both are not subclass of
                    base_representaion then compile time erorr is generated*/
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of
                        <boost::astronomy::coordinate::base_differential, ReturnType>::value),
                        "return type is expected to be a differential class");

                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint;
                    double mag = this->magnitude();     //magnitude of vector stored in current object
                    boost::geometry::transform(this->point, tempPoint); //converting coordinate/vector into cartesian

                                                                        //performing calculations to find unit vector
                    boost::geometry::set<0>(tempPoint, (boost::geometry::get<0>(tempPoint) / mag));
                    boost::geometry::set<1>(tempPoint, (boost::geometry::get<1>(tempPoint) / mag));
                    boost::geometry::set<2>(tempPoint, (boost::geometry::get<2>(tempPoint) / mag));

                    return ReturnType(tempPoint);
                }

                // magnitude of the current class is returned
                double magnitude() const
                {
                    double result = 0.0;
                    boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> tempPoint;
                    boost::geometry::transform(this->point, tempPoint);

                    switch (DimensionCount)
                    {
                    case 2:
                        result += std::pow(boost::geometry::get<0>(tempPoint), 2);
                        result += std::pow(boost::geometry::get<1>(tempPoint), 2);
                        break;
                    case 3:
                        result += std::pow(boost::geometry::get<0>(tempPoint), 2);
                        result += std::pow(boost::geometry::get<1>(tempPoint), 2);  
                        result += std::pow(boost::geometry::get<2>(tempPoint), 2);
                        break;
                    default:
                        return -1;
                    }

                    return std::sqrt(result);
                }

                // converts current representation into specified representation
                template <typename ReturnType>
                ReturnType to_differential() const
                {
                    /*checking return type if they both are not subclass of
                    base_representaion then compile time erorr is generated*/
                    BOOST_STATIC_ASSERT_MSG((boost::is_base_template_of<boost::astronomy::coordinate::base_differential, ReturnType>),
                        "return type is expected to be a differential class");

                    return ReturnType(this->point);
                }

                // returns the differential of calling object
                boost::geometry::model::point<double, DimensionCount, Type> get_differential() const
                {
                    return this->diff;
                }


            };
        } // namespace coordinate
    } // namespace astronomy
} // namespace boost

#endif // !BOOST_ASTRONOMY_COORDINATE_BASE_DIFFERENTIAL_HPP
