#include <chrono>
#include <functional>
#include <stdexcept>
#include <thread>
#include <utility>

class TimeStep {
public:
  explicit TimeStep(float updates_per_second)
      : target_delta(std::chrono::duration<float>(1.0f / updates_per_second)),
        last_time(std::chrono::steady_clock::now()), accumulated_time(0.0f),
        max_delta(
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
    duration<float> frame_time = current_time - last_time;
    last_time = current_time;

    if (frame_time > max_delta) {
      frame_time = max_delta;
    }

    accumulated_time += frame_time.count();

    while (accumulated_time >= target_delta.count()) {
      update_fn(target_delta.count());
      accumulated_time -= target_delta.count();
    }

    auto sleep_time = target_delta - (steady_clock::now() - current_time);
    if (sleep_time > duration<float>(0.f)) {
      std::this_thread::sleep_for(sleep_time);
    }
  }

  [[nodiscard]] float get_interpolation_factor() const noexcept {
    return accumulated_time / target_delta.count();
  }

private:
  std::chrono::duration<float> target_delta;
  std::chrono::steady_clock::time_point last_time;
  float accumulated_time;
  std::chrono::duration<float> max_delta;
};
