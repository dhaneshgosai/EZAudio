//
//  EZAudio.h
//  EZAudio
//
//  Created by Syed Haris Ali on 11/21/13.
//  Copyright (c) 2013 Syed Haris Ali. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import <Foundation/Foundation.h>

#pragma mark - 3rd Party Utilties
#import "AEFloatConverter.h"
#import "TPCircularBuffer.h"

#pragma mark - Core Components
#import "EZAudioFile.h"
#import "EZMicrophone.h"
#import "EZOutput.h"
#import "EZRecorder.h"

#pragma mark - Interface Components
#import "EZPlot.h"
#import "EZAudioPlot.h"
#import "EZAudioPlotGL.h"
#import "EZAudioPlotGLKViewController.h"

/**
 EZAudio is a simple, intuitive framework for iOS and OSX. The goal of EZAudio was to provide a modular, cross-platform framework to simplify performing everyday audio operations like getting microphone input, creating audio waveforms, recording/playing audio files, etc. The visualization tools like the EZAudioPlot and EZAudioPlotGL were created to plug right into the framework's various components and provide highly optimized drawing routines that work in harmony with audio callback loops. All components retain the same namespace whether you're on an iOS device or a Mac computer so an EZAudioPlot understands it will subclass an UIView on an iOS device or an NSView on a Mac.

 Class methods for EZAudio are provided as utility methods used throughout the other modules within the framework. For instance, these methods help make sense of error codes (checkResult:operation:), map values betwen coordinate systems (MAP:leftMin:leftMax:rightMin:rightMax:), calculate root mean squared values for buffers (RMS:length:), etc.
 */
@interface EZAudio : NSObject

#pragma mark - AudioBufferList Utility
///-----------------------------------------------------------
/// @name AudioBufferList Utility
///-----------------------------------------------------------

/**
 Allocates an AudioBufferList structure. Make sure to call freeBufferList when done using AudioBufferList or it will leak.
 @return An AudioBufferList struct that has been allocated in memory
 */
+(AudioBufferList*)audioBufferList;

/**
 Deallocates an AudioBufferList structure from memory.
 @param bufferList A pointer to the buffer list you would like to free
 */
+(void)freeBufferList:(AudioBufferList*)bufferList;

#pragma mark - AudioStreamBasicDescription Utilties
///-----------------------------------------------------------
/// @name AudioStreamBasicDescription Utilities
///-----------------------------------------------------------

/**
 Nicely logs out the contents of an AudioStreamBasicDescription struct
 @param 	asbd 	The AudioStreamBasicDescription struct with content to print out
 */
+(void)printASBD:(AudioStreamBasicDescription)asbd;

/**
 Just a wrapper around the setCanonical function provided in the Core Audio Utility C++ class.
 @param asbd        The AudioStreamBasicDescription structure to modify
 @param nChannels   The number of expected channels on the description
 @param interleaved A flag indicating whether the stereo samples should be interleaved in the buffer
 */
+(void)setCanonicalAudioStreamBasicDescription:(AudioStreamBasicDescription)asbd
                              numberOfChannels:(UInt32)nChannels
                                   interleaved:(BOOL)interleaved;

#pragma mark - OSStatus Utility
///-----------------------------------------------------------
/// @name OSStatus Utility
///-----------------------------------------------------------

/**
 Basic check result function useful for checking each step of the audio setup process
 @param result    The OSStatus representing the result of an operation
 @param operation A string (const char, not NSString) describing the operation taking place (will print if fails)
 */
+(void)checkResult:(OSStatus)result
         operation:(const char*)operation;

#pragma mark - Math Utilities
///-----------------------------------------------------------
/// @name Math Utilities
///-----------------------------------------------------------

/**
 Maps a value from one coordinate system into another one. Takes in the current value to map, the minimum and maximum values of the first coordinate system, and the minimum and maximum values of the second coordinate system and calculates the mapped value in the second coordinate system's constraints.
 @param 	value 	The value expressed in the first coordinate system
 @param 	leftMin 	The minimum of the first coordinate system
 @param 	leftMax 	The maximum of the first coordinate system
 @param 	rightMin 	The minimum of the second coordindate system
 @param 	rightMax 	The maximum of the second coordinate system
 @return	The mapped value in terms of the second coordinate system
 */
+(float)MAP:(float)value
    leftMin:(float)leftMin
    leftMax:(float)leftMax
   rightMin:(float)rightMin
   rightMax:(float)rightMax;

/**
 Calculates the root mean squared for a buffer.
 @param 	buffer 	A float buffer array of values whose root mean squared to calculate
 @param 	bufferSize 	The size of the float buffer
 @return	The root mean squared of the buffer
 */
+(float)RMS:(float*)buffer
     length:(int)bufferSize;

@end
