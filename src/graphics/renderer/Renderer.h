
template <class T>
class Renderer
{
protected:
	Renderer() = default;
public:
	virtual ~Renderer() = default;

	virtual void addToRenderQueue(T) = 0;
	virtual void render() = 0;
};