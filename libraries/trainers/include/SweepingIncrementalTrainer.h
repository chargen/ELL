////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     SweepingIncrementalTrainer.h (trainers)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "EvaluatingIncrementalTrainer.h"
#include "ITrainer.h"
#include "MultiEpochIncrementalTrainer.h"

// data
#include "Dataset.h"

// evaluators
#include "Evaluator.h"

//stl
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

namespace ell
{
namespace trainers
{
    /// <summary> A class that runs multiple internal trainers and chooses the best performing predictor. </summary>
    ///
    /// <typeparam name="PredictorType"> The type of predictor returned by this trainer. </typeparam>
    template <typename PredictorType>
    class SweepingIncrementalTrainer : public ITrainer<PredictorType>
    {
    public:
        typedef EvaluatingIncrementalTrainer<PredictorType> EvaluatingTrainerType;

        /// <summary> Constructs an instance of SweepingIncrementalTrainer. </summary>
        ///
        /// <param name="evaluatingTrainers"> A vector of evaluating trainers. </param>
        /// <param name="parameters"> Multi-epoch training parameter. </param>
        SweepingIncrementalTrainer(std::vector<EvaluatingTrainerType>&& evaluatingTrainers, const MultiEpochIncrementalTrainerParameters& parameters);

        /// <summary> Updates the state of the trainer by performing a learning epoch. </summary>
        ///
        /// <param name="anyDataset"> A dataset. </param>
        virtual void Update(const data::AnyDataset& anyDataset) override;

        /// <summary> Gets a const reference to the current predictor. </summary>
        ///
        /// <returns> A const reference to the current predictor. </returns>
        virtual const PredictorType& GetPredictor() const override;

    private:
        std::vector<EvaluatingTrainerType> _evaluatingTrainers;
        MultiEpochIncrementalTrainerParameters _parameters;
        mutable std::default_random_engine _random;
    };

    /// <summary> Makes an incremental trainer that runs multiple internal trainers and chooses the best performing predictor. </summary>
    ///
    /// <typeparam name="PredictorType"> Type of the predictor returned by this trainer. </typeparam>
    /// <param name="evaluatingTrainers"> A vector of evaluating trainers. </param>
    ///
    /// <returns> A unique_ptr to a sweeping trainer. </returns>
    template <typename PredictorType>
    std::unique_ptr<ITrainer<PredictorType>> MakeSweepingIncrementalTrainer(std::vector<EvaluatingIncrementalTrainer<PredictorType>>&& evaluatingTrainers, const MultiEpochIncrementalTrainerParameters& parameters);
}
}

#include "../tcc/SweepingIncrementalTrainer.tcc"
