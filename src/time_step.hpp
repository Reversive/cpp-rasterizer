#include <chrono>
#include <functional>
#include <stdexcept>
#include <thread>
#include <utility>

class TimeStep {
public:
  explicit TimeStep(float updates_per_second)
      : m_target_delta(std::chrono::duration<float>(1.0f / updates_per_second)),
        m_last_time(std::chrono::steady_clock::now()), m_accumulated_time(0.0f),
        m_max_delta(
            std::chrono::duration<float>(0.25f)) // Prevent spiral of death
  {
    if (updates_per_second <= 0.0f) {
      throw std::invalid_argument("Updates per second must be positive");
    }
  }

  TimeStep(const TimeStep &) = delete;
  TimeStep &operator=(const TimeStep &) = delete;

  TimeStep(TimeStep &&) noexcept = default;
  TimeStep &operator=(TimeStep &&) noexcept = default;

  template <typename UpdateFn> void update(UpdateFn &&update_fn) {
    using namespace std::chrono;

    auto current_time = steady_clock::now();
    duration<float> frame_time = current_time - m_last_time;
    m_last_time = current_time;

    if (frame_time > m_max_delta) {
      frame_time = m_max_delta;
    }

    m_accumulated_time += frame_time.count();

    while (m_accumulated_time >= m_target_delta.count()) {
      update_fn(m_target_delta.count());
      m_accumulated_time -= m_target_delta.count();
    }

    auto sleep_time = m_target_delta - (steady_clock::now() - current_time);
    if (sleep_time > duration<float>(0.f)) {
      std::this_thread::sleep_for(sleep_time);
    }
  }

  [[nodiscard]] float getInterpolationFactor() const noexcept {
    return m_accumulated_time / m_target_delta.count();
  }

private:
  std::chrono::duration<float> m_target_delta;
  std::chrono::steady_clock::time_point m_last_time;
  float m_accumulated_time;
  std::chrono::duration<float> m_max_delta;
};
