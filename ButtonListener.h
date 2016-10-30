#ifndef BUTTONLISTENER_H
#define BUTTONLISTENER_H

class Button;

/*
 * Author: wcrane
 * Date: 5/12/2013
 *
 * Interface that allows you to respond to button clicks.
 */
class ButtonListener
{
public:
	virtual void buttonClicked(Button *button) = 0;
};

#endif