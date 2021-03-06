////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     LoadModel.h (common)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MapLoadArguments.h"

// model
#include "DynamicMap.h"
#include "Model.h"

namespace ell
{
namespace common
{
    /// <summary> Loads a model from a file, or creates a new one if given an empty filename. </summary>
    ///
    /// <param name="filename"> The filename. </param>
    /// <returns> The loaded model. </returns>
    model::Model LoadModel(const std::string& filename);

    /// <summary> Saves a model to a file. </summary>
    ///
    /// <param name="model"> The model. </param>
    /// <param name="filename"> The filename. </param>
    void SaveModel(const model::Model& model, const std::string& filename);

    /// <summary> Saves a model to a stream. </summary>
    ///
    /// <param name="model"> The model. </param>
    /// <param name="outStream"> The stream. </param>
    /// <param name="filetype"> The format for the output ('xml' or 'json') </param>
    void SaveModel(const model::Model& model, std::ostream& outStream, std::string filetype);

    /// <summary> Register known node types to a serialization context </summary>
    ///
    /// <param name="context"> The `SerializationContext` </param>
    void RegisterNodeTypes(utilities::SerializationContext& context);

    /// <summary> Loads a map from a file, or creates a new one if given an empty filename. </summary>
    ///
    /// <param name="filename"> The filename. </param>
    /// <returns> The loaded map. </returns>
    model::DynamicMap LoadMap(const std::string& filename);

    /// <summary> Loads a map from a `MapLoadArguments` struct. </summary>
    ///
    /// <param name="mapLoadArguments"> The `MapLoadArguments` struct. </param>
    /// <returns> The loaded map. </returns>
    model::DynamicMap LoadMap(const MapLoadArguments& mapLoadArguments);

    /// <summary> Saves a map to a file. </summary>
    ///
    /// <param name="map"> The map. </param>
    /// <param name="filename"> The filename. </param>
    void SaveMap(const model::DynamicMap& map, const std::string& filename);

    /// <summary> Saves a map to a stream. </summary>
    ///
    /// <param name="map"> The map. </param>
    /// <param name="outStream"> The stream. </param>
    /// <param name="filetype"> The format for the output ('xml' or 'json') </param>
    void SaveMap(const model::DynamicMap& map, std::ostream& outStream, std::string filetype);
}
}
