#pragma once

#include "Cazel/Core.h"
#include "czpch.h"

namespace Cazel {
/// Events in Cazel are currently blocking, meaning when an event
/// occurs, it immediately gets dispatched and must be dealt at once.
/// For the future, a better strategy might be to buffer events in an
/// event bus and process them during the "event" part of the update stage.

enum class EventType {
  None = 0,
  // window
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,
  // app
  AppTick,
  AppUpdate,
  AppRender,
  // key
  KeyPressed,
  KeyReleased,
  KeyTyped,
  // mouse
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

/// @brief 对上述 EventType 进行归类
/// 可以使用 item_category & category 位运算判断某 event 的
/// category 是否包括某 category，如果不等于 0，则包括该 category
/// 例如，KeyEvent 的 category 是 EventCategoryKeyboard | EventCategoryInput，
/// 这样使用位运算计算 event 的 category 和 EventCategoryKeyboard 或
/// EventCategoryInput 的结果都会是不等于 0 的
enum EventCategory {
  None = 0,
  EventCategoryApplication = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryKeyboard = BIT(2),
  EventCategoryMouse = BIT(3),
  EventCategoryMouseButton = BIT(4)
};

// ## 号是连接符
// # 号用于获取其字符串表示
#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

class CAZEL_API Event {
 public:
  bool Handled = false;

  virtual EventType GetEventType() const = 0;
  virtual const char *GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); };

  inline bool IsInCategory(EventCategory category) {
    return GetCategoryFlags() & category;
  }
};

class EventDispatcher {
  /// @brief Event callback, it will return whether this
  /// event shall still be propagated.
  /// @tparam T Event Type
  template <typename T>
  using EventFn = std::function<bool(T &)>;

 public:
  EventDispatcher(Event &event) : m_Event(event) {}

  template <typename T>
  bool Dispatch(EventFn<T> func) {
    if (m_Event.GetEventType() == T::GetStaticType()) {
      m_Event.Handled = func(*dynamic_cast<T *>(&m_Event));  // 向下转型
      return true;
    }
    return false;
  }

 private:
  Event &m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e) {
  return os << e.ToString();
}
}  // namespace Cazel