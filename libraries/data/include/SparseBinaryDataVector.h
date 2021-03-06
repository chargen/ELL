////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     SparseBinaryDataVector.h (data)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DataVector.h"
#include "IndexValue.h"

#ifndef SPARSEBINARYDATAVECTOR_H
#define SPARSEBINARYDATAVECTOR_H

// utilities
#include "CompressedIntegerList.h"
#include "IntegerList.h"

// stl
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>

namespace ell
{
namespace data
{
    /// <summary> Implements a sparse binary vector as an increasing list of the coordinates where the
    /// value is 1.0. </summary>
    ///
    /// <typeparam name="tegerListType"> Type of the teger list type. </typeparam>
    template <typename IntegerListType>
    class SparseBinaryDataVectorBase : public DataVectorBase<SparseBinaryDataVectorBase<IntegerListType>>
    {
    public:
        /// <summary> A read-only forward iterator for the sparse binary vector. </summary>
        class Iterator : public IIndexValueIterator
        {
        public:
            Iterator(const Iterator&) = default;

            Iterator(Iterator&&) = default;

            /// <summary> Returns true if the iterator is currently pointing to a valid iterate. </summary>
            ///
            /// <returns> true if it succeeds, false if it fails. </returns>
            bool IsValid() const { return _list_iterator.IsValid(); }

            /// <summary> Proceeds to the Next iterate. </summary>
            void Next() { _list_iterator.Next(); }

            /// <summary> Returns The current value. </summary>
            ///
            /// <returns> An IndexValue. </returns>
            IndexValue Get() const { return IndexValue{ _list_iterator.Get(), 1.0 }; }

        private:
            /// <summary> define typename to improve readability. </summary>
            using IndexIteratorType = typename IntegerListType::Iterator;

            /// <summary> private ctor, can only be called from SparseBinaryDataVectorBase class. </summary>
            ///
            /// <param name="list_iterator"> The list iterator. </param>
            Iterator(const typename IntegerListType::Iterator& list_iterator);
            friend SparseBinaryDataVectorBase<IntegerListType>;

            // members
            IndexIteratorType _list_iterator;
        };

        SparseBinaryDataVectorBase() = default;

        SparseBinaryDataVectorBase(SparseBinaryDataVectorBase<IntegerListType>&& other) = default;

        SparseBinaryDataVectorBase(const SparseBinaryDataVectorBase<IntegerListType>& other) = delete;

        /// <summary> Constructs a DenseDataVector from an index value iterator. </summary>
        ///
        /// <typeparam name="IndexValueIteratorType"> Type of index value iterator. </typeparam>
        /// <param name="IndexValueIterator"> The index value iterator. </param>
        template <typename IndexValueIteratorType, IsIndexValueIterator<IndexValueIteratorType> Concept = true>
        SparseBinaryDataVectorBase(IndexValueIteratorType indexValueIterator);

        /// <summary> Constructs a data vector from an initializer list of index value pairs. </summary>
        ///
        /// <param name="list"> The initializer list. </param>
        SparseBinaryDataVectorBase(std::initializer_list<IndexValue> list);

        /// <summary> Constructs a data vector from an initializer list of values. </summary>
        ///
        /// <param name="list"> The initializer list of values. </param>
        SparseBinaryDataVectorBase(std::initializer_list<double> list);

        /// <summary> Constructs a data vector from a vector of index value pairs. </summary>
        ///
        /// <param name="list"> The initializer list. </param>
        SparseBinaryDataVectorBase(std::vector<IndexValue> vec);

        /// <summary> Constructs a data vector from a vector of values. </summary>
        ///
        /// <param name="list"> The initializer list of values. </param>
        SparseBinaryDataVectorBase(std::vector<double> vec);

        /// <summary> Returns a Iterator that traverses the non-zero entries of the sparse vector. </summary>
        ///
        /// <returns> The iterator. </returns>
        Iterator GetIterator() const { return Iterator(_indices.GetIterator()); }

        /// <summary> Sets the element at the given index to 1.0. Calls to this function must have a
        /// monotonically increasing argument. The value argument must equal 1.0. </summary>
        ///
        /// <param name="index"> Zero-based index of the. </param>
        /// <param name="value"> The value. </param>
        virtual void AppendElement(size_t index, double value) override;

        /// <summary>
        /// A data vector has infinite dimension and ends with a suffix of zeros. This function returns
        /// the first index in this suffix. Equivalently, the returned value is one plus the index of the
        /// last non-zero element.
        /// </summary>
        ///
        /// <returns> The first index of the suffix of zeros at the end of this vector. </returns>
        virtual size_t PrefixLength() const override;

        /// <summary> Computes the vector squared 2-norm. </summary>
        ///
        /// <returns> A double. </returns>
        virtual double Norm2() const override { return std::sqrt(_indices.Size()); }

        /// <summary> Computes the Dot product. </summary>
        ///
        /// <param name="p_other"> The other. </param>
        ///
        /// <returns> A double. </returns>
        virtual double Dot(const math::UnorientedConstVectorReference<double> vector) const override;

        /// <summary> Performs vector += scalar * (*this), where other a dense vector. </summary>
        ///
        /// <param name="vector"> [in,out] The vector that this DataVector is added to. </param>
        /// <param name="scalar">  The scalar. </param>
        virtual void AddTo(math::RowVectorReference<double> vector, double scalar = 1.0) const override;

    private:
        using DataVectorBase<SparseBinaryDataVectorBase<IntegerListType>>::AppendElements;
        IntegerListType _indices;
    };

    /// <summary> A sparse data vector with binary elements. </summary>
    struct SparseBinaryDataVector : public SparseBinaryDataVectorBase<utilities::CompressedIntegerList>
    {
        using SparseBinaryDataVectorBase<utilities::CompressedIntegerList>::SparseBinaryDataVectorBase;

        /// <summary> Gets the data vector type. </summary>
        ///
        /// <returns> The data vector type. </returns>
        virtual IDataVector::Type GetType() const override { return IDataVector::Type::SparseBinaryDataVector; }
    };
}
}

#include "../tcc/SparseBinaryDataVector.tcc"

#endif // SPARSEBINARYDATAVECTOR_H
