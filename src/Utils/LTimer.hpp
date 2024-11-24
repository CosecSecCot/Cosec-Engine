#ifndef LTimer_hpp
#define LTimer_hpp
#pragma once

#include "SDL_stdinc.h"
#include "SDL_timer.h"

class LTimer {
public:
    // Initializes variables
    LTimer() {
        // Initialize the variables
        startTicks = 0;
        pausedTicks = 0;

        paused = false;
        started = false;
    }

    // The various clock actions
    void start() {
        // Start the timer
        started = true;

        // Unpause the timer
        paused = false;

        // Get the current clock time
        startTicks = SDL_GetTicks();
        pausedTicks = 0;
    }

    void stop() {
        // Stop the timer
        started = false;

        // Unpause the timer
        paused = false;

        // Clear tick variables
        startTicks = 0;
        pausedTicks = 0;
    }

    void pause() {
        // If the timer is running and isn't already paused
        if (started && !paused) {
            // Pause the timer
            paused = true;

            // Calculate the paused ticks
            pausedTicks = SDL_GetTicks() - startTicks;
            startTicks = 0;
        }
    }

    void unpause() {
        // If the timer is running and paused
        if (started && paused) {
            // Unpause the timer
            paused = false;

            // Reset the starting ticks
            startTicks = SDL_GetTicks() - pausedTicks;

            // Reset the paused ticks
            pausedTicks = 0;
        }
    }

    // Gets the timer's time
    [[nodiscard]] Uint32 getTicks() const {
        // The actual timer time
        Uint32 time = 0;

        // If the timer is running
        if (started) {
            // If the timer is paused
            if (paused) {
                // Return the number of ticks when the timer was paused
                time = pausedTicks;
            } else {
                // Return the current time minus the start time
                time = SDL_GetTicks() - startTicks;
            }
        }

        return time;
    }

    // Checks the status of the timer
    [[nodiscard]] bool isStarted() const {
        // Timer is running and paused or unpaused
        return started;
    }

    [[nodiscard]] bool isPaused() const {
        // Timer is running and paused
        return paused && started;
    }

private:
    // The clock time when the timer started
    Uint32 startTicks;

    // The ticks stored when the timer was paused
    Uint32 pausedTicks;

    // The timer status
    bool paused;
    bool started;
};

#endif /* LTimer.hpp */
