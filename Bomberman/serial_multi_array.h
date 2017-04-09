/* Part of this code was submitted through the mailing list of boost 
	as an addition to boost serialization to support boost.MultiArray.
	Although not yet in boost, it might come in a later part.
	Therefor I am not fully the owner of this whole code, but I consider
	that most of this code already is in boost.
*/

#ifndef SERIAL_MULTI_ARRAY
#define SERIAL_MULTI_ARRAY

#include <boost/multi_array.hpp>
#include <boost/serialization/array.hpp>

namespace boost {
	namespace serialization {
		template<class Archive, class T, std::size_t N>
		inline void save(Archive & ar, const boost::multi_array<T, N> & mt, const unsigned int file_version) {
			ar << boost::serialization::make_nvp("dimensions", 
				boost::serialization::make_array(mt.shape(), N));
			ar << boost::serialization::make_nvp("data", 
				boost::serialization::make_array(mt.data(), mt.num_elements()));
		}

		template<class Archive, class T, std::size_t N>
		inline void load(Archive & ar, boost::multi_array<T, N> & mt, const unsigned int file_version) {
			typedef boost::multi_array<T,N>::size_type size_type;
			
			boost::array<size_type, N> dimensions;
			ar >> boost::serialization::make_nvp("dimensions",
				boost::serialization::make_array(dimensions.c_array(), N));
			mt.resize(dimensions);
			ar >> boost::serialization::make_nvp("data",
				boost::serialization::make_array(mt.data(), mt.num_elements()));
		}

		template<class Archive, class T, std::size_t N>
		inline void serialize(Archive & ar, boost::multi_array<T, N> & mt, const unsigned int file_version) {
			split_free(ar, mt, file_version);
		}
	}
}

#endif