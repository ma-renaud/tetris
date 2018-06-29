// From Raoul Borges found at https://fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance

#ifndef TETRIS_CLONEABLE_H
#define TETRIS_CLONEABLE_H

#include <memory>

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class abstract_method
{
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class virtual_inherit_from : virtual public T
{
  using T::T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Derived, typename ... Bases>
class clone_inherit : public Bases...
{
public:
  virtual ~clone_inherit() = default;

  std::unique_ptr<Derived> clone() const
  {
    return std::unique_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
  }

protected:
  //         desirable, but impossible in C++17
  //         see: http://cplusplus.github.io/EWG/ewg-active.html#102
  // using typename... Bases::Bases;

private:
  virtual clone_inherit * clone_impl() const override
  {
    return new Derived(static_cast<const Derived & >(*this));
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename Derived, typename ... Bases>
class clone_inherit<abstract_method<Derived>, Bases...> : public Bases...
{
public:
  virtual ~clone_inherit() = default;

  std::unique_ptr<Derived> clone() const
  {
    return std::unique_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
  }

protected:
  //         desirable, but impossible in C++17
  //         see: http://cplusplus.github.io/EWG/ewg-active.html#102
  // using typename... Bases::Bases;

private:
  virtual clone_inherit * clone_impl() const = 0;
};

///////////////////////////////////////////////////////////////////////////////

template <typename Derived>
class clone_inherit<Derived>
{
public:
  virtual ~clone_inherit() = default;

  std::unique_ptr<Derived> clone() const
  {
    return std::unique_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
  }

private:
  virtual clone_inherit * clone_impl() const override
  {
    return new Derived(static_cast<const Derived & >(*this));
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename Derived>
class clone_inherit<abstract_method<Derived>>
{
public:
  virtual ~clone_inherit() = default;

  std::unique_ptr<Derived> clone() const
  {
    return std::unique_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
  }

private:
  virtual clone_inherit * clone_impl() const = 0;
};

#endif //TETRIS_CLONEABLE_H
