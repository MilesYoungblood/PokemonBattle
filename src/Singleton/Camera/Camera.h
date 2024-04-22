//
// Created by Miles Youngblood on 10/11/2023.
//

#pragma once

class Map;

class Camera {
public:
    /// \brief Getter for Singleton instance
    /// \return the Camera instance
    static Camera &getInstance();

    /// \brief Determines whether a rectangle is in view of the camera
    /// \details This function's purpose is to enable the rendering of only
    /// necessary objects. It is useless to render objects that are not
    /// onscreen, not to mention costly. This function eliminates this problem.
    /// \param rect the rectangle to check
    /// \return true if the rectangle is in view, false otherwise
    [[nodiscard]] bool isInView(SDL_Rect rect) const;

    /// \brief Finds the player's current position on the screen,
    /// then shifts everything, including the player, accordingly.
    /// \param map the map
    void lockOnPlayer(Map &map) const;

private:
    SDL_Rect view;

    Camera();
};
