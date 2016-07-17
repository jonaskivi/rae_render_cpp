/*
* The X11/MIT License
* 
* Copyright (c) 2008-2011, Jonas Kivi
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef _rae_ui_Input_hpp_
#define _rae_ui_Input_hpp_

#include "ui/KeySym.hpp"

#include <iostream>
#include <vector>
#include <functional>

#include "core/version.hpp"

#include "core/ScreenSystem.hpp"

namespace Rae
{

namespace TouchPointState
{
	enum e
	{
		UNDEFINED,
		PRESSED, //finger touched the screen on last frame
		RELEASED, //finger left the screen on last frame
		MOVED, //finger position moved
		STATIONARY //i.e. didn't move from last frame
	};
}

// Notice that:
// Gtk  MIDDLE = 2, RIGHT = 3
// GLFW MIDDLE = 3, RIGHT = 2

#ifdef version_cocoa
namespace MouseButton
{
	enum e
	{
		UNDEFINED = 0,
		FIRST,// = 1,
		MIDDLE,
		SECOND,
		FOURTH,
		FIFTH
	};
};
#endif
#ifdef version_glfw
namespace MouseButton
{
	enum e
	{
		UNDEFINED = -1,
		FIRST = 0,// = 1,
		SECOND,
		MIDDLE,
		FOURTH,
		FIFTH
	};
};
#endif


namespace EventType
{
	enum e
	{
		UNDEFINED,
		MOUSE_MOTION,
		MOUSE_BUTTON_PRESS,
		MOUSE_BUTTON_RELEASE,
		// since multitouch has so many beginnings, updates and ends,
		// we don't do separate events, but you'll have to track them yourself,
		// from the states and lists of touchpoints.
		TOUCH,
		KEY_PRESS,
		KEY_RELEASE,
		KEY_HOLD,
		ENTER_NOTIFY,
		LEAVE_NOTIFY,
		SCROLL
	};
}


class Input
{
public:
	Input(ScreenSystem& screenSystem)
	: m_screenSystem(screenSystem),
	eventType(EventType::UNDEFINED),
	isHandled(false)
	{
	
	}

	EventType::e eventType;
	//IRectangle* eventWindow;	
	bool isHandled;
	
	struct Mouse
	{
		Mouse()
		: eventButton(0),
			//button((bool[]){false, false, false, false, false, false}),
			doubleClickButton(0),
			x(0.0f),
			y(0.0f),
			xLocal(0.0f),
			yLocal(0.0f),
			xRel(0.0f),
			yRel(0.0f),
			xRelLocal(0.0f),
			yRelLocal(0.0f),
			xP(0.0f),
			yP(0.0f),
			xLocalP(0.0f),
			yLocalP(0.0f),
			xRelP(0.0f),
			yRelP(0.0f),
			xRelLocalP(0.0f),
			yRelLocalP(0.0f),
			amount(0.0f),
			//onButtonPress locations:
			/*
			xOnButtonPress((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			yOnButtonPress((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			xRelOnButtonPress((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			yRelOnButtonPress((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			xOnButtonPressP((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			yOnButtonPressP((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			xRelOnButtonPressP((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			yRelOnButtonPressP((float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}),
			*/
			scrollX(0.0f),
			scrollY(0.0f)
		{
			for(uint i = 0; i < 6; i++)
				m_button[i] = false;

			for(uint i = 0; i < 6; i++)
				xOnButtonPress[i] = 0.0f;
			for(uint i = 0; i < 6; i++)
				yOnButtonPress[i] = 0.0f;
			for(uint i = 0; i < 6; i++)
				xRelOnButtonPress[i] = 0.0f;
			for(uint i = 0; i < 6; i++)
				yRelOnButtonPress[i] = 0.0f;
			for(uint i = 0; i < 6; i++)
				xOnButtonPressP[i] = 0.0f;
			for(uint i = 0; i < 6; i++)
				yOnButtonPressP[i] = 0.0f;
			for(uint i = 0; i < 6; i++)
				xRelOnButtonPressP[i] = 0.0f;
			for(uint i = 0; i < 6; i++)
				yRelOnButtonPressP[i] = 0.0f;
		}
	
		bool button(MouseButton::e but) const
		{
			return m_button[(int)but];
		}

		void setButton(MouseButton::e but, bool set)
		{
			m_button[(int)but] = set;
		}

		uint eventButton;// = 0;
	protected:
		bool m_button[6];
	public:
		uint doubleClickButton;// = 0;
		//in height coordinates:
		float x;// = 0.0;
		float y;// = 0.0;
		float xLocal;// = 0.0;//These change all the time.
		float yLocal;// = 0.0;
		float xRel;// = 0.0;
		float yRel;// = 0.0;
		float xRelLocal;// = 0.0;
		float yRelLocal;// = 0.0;
		//in pixels:
		float xP;// = 0.0;
		float yP;// = 0.0;
		float xLocalP;// = 0.0;//These change all the time.
		float yLocalP;// = 0.0;
		float xRelP;// = 0.0;
		float yRelP;// = 0.0;
		float xRelLocalP;// = 0.0;
		float yRelLocalP;// = 0.0;
		
		float amount;// = 0.0f;
		//onButtonPress locations:
		float xOnButtonPress[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		float yOnButtonPress[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		float xRelOnButtonPress[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		float yRelOnButtonPress[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		
		//in pixels:
		float xOnButtonPressP[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		float yOnButtonPressP[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		float xRelOnButtonPressP[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		float yRelOnButtonPressP[6];// = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
		
		//Scroll events:
		float scrollX;
		float scrollY;
	};
	
	Mouse mouse;

	struct TouchPoint
	{
		TouchPoint()
		: id(0),
			state(TouchPointState::UNDEFINED),
			x(0.0f),
			y(0.0f),
			xLocal(0.0f),
			yLocal(0.0f),
			xRel(0.0f),
			yRel(0.0f),
			xRelLocal(0.0f),
			yRelLocal(0.0f),
			xP(0.0f),
			yP(0.0f),
			xLocalP(0.0f),
			yLocalP(0.0f),
			xRelP(0.0f),
			yRelP(0.0f),
			xRelLocalP(0.0f),
			yRelLocalP(0.0f)
		{
		}

		int id;

		TouchPointState::e state;

		float x;// = 0.0;
		float y;// = 0.0;
		float xLocal;// = 0.0;//These change all the time.
		float yLocal;// = 0.0;
		float xRel;// = 0.0;
		float yRel;// = 0.0;
		float xRelLocal;// = 0.0;
		float yRelLocal;// = 0.0;
		//in pixels:
		float xP;// = 0.0;
		float yP;// = 0.0;
		float xLocalP;// = 0.0;//These change all the time.
		float yLocalP;// = 0.0;
		float xRelP;// = 0.0;
		float yRelP;// = 0.0;
		float xRelLocalP;// = 0.0;
		float yRelLocalP;// = 0.0;

		void printInfo()
		{
			//RaeLog<<"TouchPoint: id: "<<id<<" "<<TouchPointState::toString(state)<<" x: "<<x<<" y: "<<y<<" xLocal: "<<xLocal<<" yLocal: "<<yLocal
			/*
			RaeLog<<"TouchPoint: id: "<<id<<" x: "<<x<<" y: "<<y<<" xLocal: "<<xLocal<<" yLocal: "<<yLocal
				<<" xRel: "<<xRel<<" yRel: "<<yRel<<" xRelLocal: "<<xRelLocal<<" yRelLocal: "<<yRelLocal
				<<" xP: "<<xP<<" yP: "<<yP<<" xLocalP: "<<xLocalP<<" yLocalP: "<<yLocalP
				<<" xRelP: "<<xRelP<<" yRelP: "<<yRelP<<" xRelLocalP: "<<xRelLocalP<<" yRelLocalP: "<<yRelLocalP<<"\n";
				*/
		}
	};



	struct Touch
	{
		Touch()
		{
			touchPoints_size = 20;

			eventId = 0;

			for(int i = 0; i < touchPoints_size; i++ )
			{
				touchPoints[i].id = i;
			}
		}

		TouchPoint* currentTouchPoint()
		{
			return &touchPoints[eventId];
		}

		int eventId;//current touch event id that we are handling.

		int touchPoints_size;// = 20
		TouchPoint touchPoints[20];
	};

	Touch touch;

	struct Keyboard
	{
		Keyboard()
		{
			for(uint i = 0; i < keyStatesSize; i++ )
			{
				keyStates[i] = false;
			}
		}

		static const uint keyStatesSize = 65536;

		uint value = 0;
		//string unicode;// = 0;
		char* unicode;
		
		bool keyStates[keyStatesSize];
	};
	Keyboard key;

	bool getKeyState(int keyValue)
	{
		if (keyValue < key.keyStatesSize)
			return key.keyStates[keyValue];
		return false;
	}

	void addTouchPoint( TouchPointState::e set_state, int set_id, float set_x_pixels, float set_y_pixels )
	{
		isHandled = false;

		eventType = EventType::TOUCH;

		//touch.addTouchPoint(set_id, set_x_pixels, set_y_pixels);
		set_x_height = m_screenSystem.pixelsToHeight(set_x_pixels);
		set_y_height = m_screenSystem.pixelsToHeight(set_y_pixels);

		#ifdef DebugTouch
			RaeLog<<"addTouchPoint: x: "<<set_x_pixels<<" y: "<<set_y_pixels<<"\n";
		#endif

		if( set_id < touch.touchPoints_size )
		{
			touch.eventId = set_id;
		}
		else
		{
			touch.eventId = 0;
			cout << "ERROR: Rae.Input.addTouchPoint. ID is over 20. id: " << set_id;
		}

		for( int i = 0; i < touch.touchPoints_size; i++ )
		{
			if( set_id == touch.touchPoints[i].id )
			{
				touch.touchPoints[i].state = set_state;

				touch.touchPoints[i].xRelP = set_x_pixels - touch.touchPoints[i].xP;
				touch.touchPoints[i].yRelP = set_y_pixels - touch.touchPoints[i].yP;
				touch.touchPoints[i].xRel = set_x_height - touch.touchPoints[i].x;
				touch.touchPoints[i].yRel = set_y_height - touch.touchPoints[i].y;

				touch.touchPoints[i].xP = set_x_pixels;
				touch.touchPoints[i].yP = set_y_pixels;
				touch.touchPoints[i].x = set_x_height;
				touch.touchPoints[i].y = set_y_height;

				/*
				//Do we need to init these?
				touch.touchPoints[i].xLocalP = set_x_pixels;
				touch.touchPoints[i].yLocalP = set_y_pixels;
				touch.touchPoints[i].xLocal = set_x_height;
				touch.touchPoints[i].yLocal = set_y_height;
				*/
				return;//success
			}
		}
		cout << "Rae::Input ERROR: Touch ID not found. id: " << set_id << "\n";
	}

	void scrollEvent( float set_delta_x, float set_delta_y )
	{
		isHandled = false;
		eventType = EventType::SCROLL;
		
		mouse.scrollX = set_delta_x;
		mouse.scrollY = set_delta_y;

		for (auto&& slot : scrollSlots)
		{
			slot(*this);
		}
	}
	
	void keyEvent( EventType::e set_event_type, int set_key, int32_t set_unicode )
	{
		//Trace.formatln("Input.keyEvent() set_key: {}", set_key );

		isHandled = false;
		//window = set_window;
		eventType = set_event_type;
		
		key.value = set_key;
		//key.unicode = set_unicode;
		
		/*
		version(gtk)
		{
			key.value = set_key;
			key.unicode = keyValueToUnicode(set_key);
		}
		version(glfw)
		{
			key.value = set_key;
			key.unicode = cast(dchar) set_key;
		}
		*/
		
		if( set_event_type == EventType::KEY_PRESS )
		{
			//cout << "KEY_PRESS: " << hex << set_key << dec << " unicode: " << set_unicode <<"\n";
			if( key.value < key.keyStatesSize )
				key.keyStates[key.value] = true;
			else cout << "ERROR: key.value: " << key.value << " is bigger than keyStatesSize: " << key.keyStatesSize << "\n";
			//Trace.formatln("PRESS. {}", key.keyStates[set_key]);
		}
		else if( set_event_type == EventType::KEY_RELEASE )
		{
			//cout << "KEY_RELEASE: " << hex << set_key << dec << " unicode: " << set_unicode <<"\n";
			if( key.value < key.keyStatesSize )
				key.keyStates[key.value] = false;
			else cout << "ERROR: key.value: " << key.value << " is bigger than keyStatesSize: " << key.keyStatesSize << "\n";
			//Trace.formatln("RELEASE. {}", key.keyStates[set_key]);
		}
			
		for (auto&& slot : keyEventSlots)
		{
			slot(*this);
		}
	}

	float set_x_height;
	float set_y_height;
	void mouseEvent( /*IRectangle* set_window,*/ EventType::e set_event_type, int set_button, float set_x_pixels, float set_y_pixels, float set_amount = 0.0f )
	{
		set_x_height = m_screenSystem.pixelsToHeight(set_x_pixels);
		set_y_height = m_screenSystem.pixelsToHeight(set_y_pixels);
	
		isHandled = false;
		//eventWindow = set_window;
		eventType = set_event_type;
		
		mouse.eventButton = set_button;

		mouse.amount = set_amount;
		
		mouse.doubleClickButton = 0;//Zero this, we can only emit one double click button per event... Is that bad? Propably ok,
		//as there can only be one eventButton per event as well.

		if( eventType == EventType::MOUSE_MOTION )
		{
			/////doubleClickValid1 = false;
		}
		else if( eventType == EventType::MOUSE_BUTTON_PRESS )
		{	
			mouse.setButton((MouseButton::e)set_button, true);
			mouse.xOnButtonPressP[set_button] = set_x_pixels;
			mouse.yOnButtonPressP[set_button] = set_y_pixels;
			mouse.xOnButtonPress[set_button] = set_x_height;
			mouse.yOnButtonPress[set_button] = set_y_height;
		}
		else if( eventType == EventType::MOUSE_BUTTON_RELEASE )
		{
			/*
			//Double click handling is on button release.
			//We measure the time between mouse button releases.
			if( set_button == MouseButton.LEFT )
			{
			
				if( doubleClickValid1 == true )
				{
					if( doubleClickTimer1.stop() <= 0.75 )//Currently 0.75 sec. TODO preferences in class Rae.
					{
						//It's a double click.
						debug(mouse) Trace.formatln("Input.Double click LEFT.");
						mouse.doubleClickButton = set_button;
					}
					else
					{
						debug(mouse) Trace.formatln("Input.NO .... Double click LEFT." );
					}
					
					doubleClickTimer1.start();
				}
				else
				{
					debug(mouse) Trace.formatln("Input.Start double click timer.");
					doubleClickValid1 = true;
					doubleClickTimer1.start();
				}
			}
			*/
			mouse.setButton((MouseButton::e)set_button, false);
		}
		//else
		//{
			//Trace.formatln("Input NO PRESS.");
		//}
		
		mouse.xRelP = set_x_pixels - mouse.xP;
		mouse.yRelP = set_y_pixels - mouse.yP;
		mouse.xRel = set_x_height - mouse.x;
		mouse.yRel = set_y_height - mouse.y;
		
		//
		
		mouse.xP = set_x_pixels;
		mouse.yP = set_y_pixels;
		mouse.xLocalP = set_x_pixels;
		mouse.yLocalP = set_y_pixels;
		
		mouse.x = set_x_height;
		mouse.y = set_y_height;
		mouse.xLocal = set_x_height;
		mouse.yLocal = set_y_height;

		if( eventType == EventType::MOUSE_MOTION )
		{
			for (auto&& slot : mouseMotionSlots)
			{
				slot(*this);
			}
		}
		else if( eventType == EventType::MOUSE_BUTTON_PRESS )
		{
			for (auto&& slot : mouseButtonPressSlots)
			{
				slot(*this);
			}
		}
		else if( eventType == EventType::MOUSE_BUTTON_RELEASE )
		{
			for (auto&& slot : mouseButtonReleaseSlots)
			{
				slot(*this);
			}
		}
	}

	void registerMouseButtonPressCallback(std::function<void(const Input&)> set)
	{
		mouseButtonPressSlots.push_back(set);
	}

	void registerMouseButtonReleaseCallback(std::function<void(const Input&)> set)
	{
		mouseButtonReleaseSlots.push_back(set);
	}

	void registerMouseMotionCallback(std::function<void(const Input&)> set)
	{
		mouseMotionSlots.push_back(set);
	}

	void registerScrollCallback(std::function<void(const Input&)> set)
	{
		scrollSlots.push_back(set);
	}

	void registerKeyEventCallback(std::function<void(const Input&)> set)
	{
		keyEventSlots.push_back(set);
	}

protected:
	ScreenSystem& m_screenSystem;

	std::vector<std::function<void(const Input&)>> mouseButtonPressSlots;
	std::vector<std::function<void(const Input&)>> mouseButtonReleaseSlots;
	std::vector<std::function<void(const Input&)>> mouseMotionSlots;
	std::vector<std::function<void(const Input&)>> scrollSlots;
	std::vector<std::function<void(const Input&)>> keyEventSlots;

};//end Input

};//end Rae

#endif //_rae_ui_Input_hpp_

