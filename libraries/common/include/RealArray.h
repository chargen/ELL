// RealArray.h

#pragma once

#include "types.h"

#include <vector>
using std::vector;

#include <iostream>
using std::ostream;

namespace common
{
    template <typename ValueType>
    class RealArray : public vector<ValueType>
    {
    public:

        /// A read-only forward iterator for the sparse binary vector.
        ///
        class Iterator : public IIndexValueIterator
        {
        public:

            /// Default copy ctor
            ///
            Iterator(const Iterator&) = default;

            /// Default move ctor
            ///
            Iterator(Iterator&&) = default;

            /// \returns True if the iterator is currently pointing to a valid iterate
            ///
            bool IsValid() const;

            /// Proceeds to the Next iterate
            ///
            void Next();

            /// \returns The current index-value pair
            ///
            indexValue Get() const;

        private:

            // abbreviate iterator type, for improved readability 
            using StlIteratorType = typename vector<ValueType>::const_iterator;

            /// private ctor, can only be called from RealArray class
            Iterator(const StlIteratorType& begin, const StlIteratorType& end);
            friend RealArray<ValueType>;

            // members
            StlIteratorType _begin;
            StlIteratorType _end;
            uint64 _index = 0;
            void SkipZeros();
        };

        /// Ctor
        ///
        RealArray(uint64 size = 0);
        
        /// Default copy ctor
        ///
        RealArray(const RealArray<ValueType>&) = default;
        
        /// Default move ctor
        ///
        RealArray(RealArray<ValueType>&&) = default;

        /// Converting constructor
        ///
        template<typename IndexValueIteratorType, typename concept = enable_if_t<is_base_of<IIndexValueIterator, IndexValueIteratorType>::value>>
        RealArray(IndexValueIteratorType indexValueIterator);

        /// \returns The size of the array
        ///
        uint64 Size() const;

        /// \returns An Iterator that points to the beginning of the list.
        ///
        Iterator GetIterator() const;

        /// Prints the array to an output stream
        ///
        void Print(ostream& os) const;
    };

    template <typename ValueType>
    ostream& operator<<(ostream&, const RealArray<ValueType>&);
}

#include "../tcc/RealArray.tcc"