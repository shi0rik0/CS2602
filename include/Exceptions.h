#pragma once

#include <exception>

class InvalidArgumentError : std::exception {
	const char* what() const override {
		return "Invalid argument!";
	}
};

class OutOfRangeError : InvalidArgumentError {
	const char* what() const override {
		return "Out of range!";
	}
};

class EmptyContainerError : std::exception {
	const char* what() const override {
		return "Trying to get an element from an empty stack or queue!";
	}
};

class UnimplementedError : std::exception {
    const char* what() const override {
        return "Unimplemented";
    }
};