//
//  AvidaEDController.h
//  avida/apps/viewer-macos
//
//  Created by David on 11/30/10.
//  Copyright 2010-2011 Michigan State University. All rights reserved.
//  http://avida.devosoft.org/viewer-macos
//
//  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
//  following conditions are met:
//  
//  1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the
//      following disclaimer.
//  2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//      following disclaimer in the documentation and/or other materials provided with the distribution.
//  3.  Neither the name of Michigan State University, nor the names of contributors may be used to endorse or promote
//      products derived from this software without specific prior written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY MICHIGAN STATE UNIVERSITY AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
//  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL MICHIGAN STATE UNIVERSITY OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
//  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  Authors: David M. Bryson <david@programerror.com>
//

#import <Cocoa/Cocoa.h>

#include "apto/core.h"

#import "CoreViewListener.h"


@class AvidaAppDelegate;
@class AvidaRun;
@class MapGridView;


@interface AvidaEDController : NSWindowController <CoreViewListener, NSSplitViewDelegate, NSWindowDelegate> {
  IBOutlet NSView* analyzeView;
  IBOutlet NSView* orgView;
  IBOutlet NSView* popView;
  
  IBOutlet NSButton* btnRunState;
  IBOutlet NSTextField* txtUpdate;
  IBOutlet MapGridView* mapView;
  IBOutlet NSPopUpButton* mapViewMode;
  IBOutlet NSSlider* mapZoom;
  IBOutlet NSSplitView* mainSplitView;
  IBOutlet NSSplitView* popSplitView;
  
  AvidaAppDelegate* app;
  
  AvidaRun* currentRun;
  Avida::CoreView::cListener* listener;
  Avida::CoreView::cMap* map;
  Apto::Map<NSInteger, int> map_mode_to_color;
}

// Init and Dealloc Methods
-(id)initWithAppDelegate:(AvidaAppDelegate*)delegate;

-(void)dealloc;
-(void)finalize;


// NSWindowController Methods
-(void)windowDidLoad;


// Actions
-(IBAction)toggleRunState:(id)sender;
-(IBAction)changeMapViewMode:(id)sender;
-(IBAction)changeMapZoom:(id)sender;


// NSSplitViewDelegate Protocol
-(void)splitView:(NSSplitView*)splitView resizeSubviewsWithOldSize:(NSSize)oldSize;
-(BOOL)splitView:(NSSplitView*)splitView canCollapseSubview:(NSView*)subview;
-(CGFloat)splitView:(NSSplitView*)splitView constrainMaxCoordinate:(CGFloat)proposedMax ofSubviewAt:(NSInteger)index;
-(CGFloat)splitView:(NSSplitView*)splitView constrainMinCoordinate:(CGFloat)proposedMin ofSubviewAt:(NSInteger)index;


// NSWindowDelegate Protocol
-(void)windowWillClose:(NSNotification*)notification;


// Listener Methods
@property (readonly) Avida::CoreView::cListener* listener;

-(void)handleMap:(CoreViewMap*)object;
-(void)handleUpdate:(CoreViewUpdate*)object;


@end
