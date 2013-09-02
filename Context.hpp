#ifndef _CONTEXT_HPP_
#define _CONTEXT_HPP_


class GraphicsService;
class InputService;

struct Context
{
	GraphicsService* graphicsService_;
	InputService* inputService_;
};
#endif
