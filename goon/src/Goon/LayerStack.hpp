/**
 * @file LayerStack.hpp
 * @brief Holds all the layers for the application
 * @author Kevin Blanchard
 * @version 0.1.0
 * @date 2022-11-14
 */
#pragma once
#include <vector>
#include <Goon/Core.hpp>
#include <Goon/Layer.hpp>

namespace Goon {

    /**
     * @brief Holds all the layers that should be ran in the application
     */
    class GN_API LayerStack
    {
        public:
            /**
             * @brief Creates a layer stack
             */
            LayerStack();
            ~LayerStack();
            /**
             * @brief Adds a layer
             *
             * @param layer The layer to add
             */
            void PushLayer(Layer* layer);
            /**
             * @brief Adds an overlay, meaning it will be after all the layers
             *
             * @param overlay THe overlay layer to add
             */
            void PushOverlay(Layer* overlay);
            /**
             * @brief Remove a layer
             *
             * @param layer THe layer to remove
             */
            void PopLayer(Layer* layer);
            /**
             * @brief Remove an overlay
             *
             * @param overlay The overlay layer to remove
             */
            void PopOverlay(Layer* overlay);

            //Allows us to iterate with a range for on this structure.
            std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
            std::vector<Layer*>::iterator end() { return m_Layers.end(); }

        private:
            /**
             * @brief The actual layers in a data structure
             */
            std::vector<Layer*> m_Layers;
            /**
             * @brief The position that we will be inserting the layers, so that we can add layers before overlays
             */
            std::vector<Layer*>::iterator m_LayerInsert;

    };
}
