#include <functional>
#include <memory>
#include <mutex>
#include <type_traits>

namespace PTK {

  template<
    typename C,
    typename P = std::shared_ptr<C>,
    typename M = std::mutex,
    typename L = std::lock_guard<M>
  >
  class Box {
  public:
    using Class   = C;
    using Pointer = P;
    using Mutex   = M;
    using Lock    = L;

  private:
    std::shared_ptr<Mutex> mtx_;
    Pointer ptr_;

  public:
    Box(const Box& other)
    : mtx_(other.mtx_)
    , ptr_(other.ptr_)
    {}

    Box(const Box&&) = delete;

    Box(Class* cptr)
    : mtx_(new Mutex())
    , ptr_(cptr)
    {}

    Box& operator=(const Box& other) = delete;
    Box& operator=(const Box&& other) = delete;

    template<typename Ret, typename... Args>
    typename std::function<Ret(Args...)>::result_type use(const std::function<Ret(Class*, Args...)>& fn, Args... args) {
      Lock lock(*mtx_.get());
      return fn(ptr_.get(), args...);
    }
  };

  template<
    typename C,
    template <typename...> typename P,
    typename M = std::mutex,
    template <typename...> typename L = std::lock_guard
  >
  using TBox = Box<C, P<C>, M, L<M>>;

}
