# deltaTime

帧数是实时变动的，时而 60 帧、时而 50 帧、时而 30 帧。

为保证每秒移动的距离是一样的，就引入了 deltaTime。

1 秒 30 帧时，deltaTime = 1/30

1 秒 60 帧时，deltaTime = 1/60

1 秒 166 帧时，deltaTime = 1/166

这样，无论帧率是多少，移动的距离都是一样的，例如，当 1 秒 30 帧时，距离为 `deltaTime * 30 * 速度`，当 1 秒 60 帧 时，距离为 `deltaTime * 60 * 速度`。

这样就保证了每秒移动的距离是一样的了。

> <https://blog.csdn.net/ChinarCSDN/article/details/82914420>
