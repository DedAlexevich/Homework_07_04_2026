#include <iostream>

template< class T>
struct BiTree {
  T val;
  BiTree< T > * rt, * lt, * parent;
};

template< class T >
struct BiTreeIt {
  BiTree< T >* curr;
};

template< class T>
BiTree< T >* minimum(BiTree< T >* root)
{
  if (!root) {
    return root;
  }
  while (root->lt) {
    root = root->lt;
  }
  return root;
}

template< class T>
BiTree< T >* maximum(BiTree< T >* root)
{
  if (!root) {
    return root;
  }
  while (root->rt) {
    root = root->rt;
  }
  return root;
}

template< class T, class F >
F traverse(BiTree< T >* root, F f)
{
  if (!root) {
    return f;
  }
  BiTree< T >* next = minimum(root);
  while (next) {
    f(next->val);
    if (next->rt) {
      next = next->rt;
      next = minimum(next);
    } else {
      BiTree<T> parent = next->parent;
      while (parent && parent->lt != next) {
        next = parent;
        parent = next->parent;
      }
      next = parent;
    }
  }
}

template< class T >
T& value(BiTreeIt<T> it)
{
  return it.curr->val;
}

template< class T >
BiTreeIt< T > next(BiTreeIt<T> it)
{
  BiTree< T >* next = it.curr;
  if (next->rt) {
    next = next->rt;
    next = minimum(next);
  } else {
    BiTree<T> parent = next->parent;
    while (parent && parent->lt != next) {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return {next};
}

template< class T >
BiTreeIt< T > prev(BiTreeIt<T> it)
{
  BiTree< T >* next = it.curr;
  if (next->lt) {
    next = next->lt;
    next = maximum(next);
  } else {
    BiTree<T> parent = next->parent;
    while (parent && parent->rt != next) {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return {next};
}

template< class T >
bool hasNext(BiTreeIt<T> it)
{
  return next(it).curr;
}

template< class T >
bool hasPrev(BiTreeIt<T> it)
{
  return prev(it).curr;
}

template< class T >
struct TriTree {
  T val0, val1;
  TriTree< T > * lt, * mid, * rt, * parent;
};

template< class T >
struct TriTreeIt {
  size_t s;
  TriTree<T>* curr;
};

template< class T >
T& value(TriTreeIt<T> it)
{
  return it.s ? it.curr->val1 : it.curr->val0;
}

template<class T>
TriTree<T>* minimum(TriTree<T>* root)
{
  if (!root) {
    return root;
  }
  while (root->lt) {
    root = root->lt;
  }
  return root;
}

template<class T>
TriTree<T>* maximum(TriTree<T>* root)
{
  if (!root) {
    return root;
  }
  while (root->rt) {
    root = root->rt;
  }
  return root;
}

template< class T >
TriTreeIt< T > next(TriTreeIt<T> it)
{
  TriTree<T>* next = it.curr;
  size_t ind = it.s;

  if (!next) {
    return {0, nullptr};
  }

  if (!ind) {
    if (next->mid) {
      next = next->mid;
      next = minimum(next);
      ind = 0;
    } else {
      ind = 1;
    }
  } else {
    if (next->rt) {
      next = next->rt;
      next = minimum(next);
      ind = 0;
    } else {
      TriTree<T>* parent = next->parent;
      while (parent) {
        if (parent->lt == next) {
          ind = 0;
          break;
        }
        if (parent->mid == next) {
          ind = 1;
          break;
        }
        next = parent;
        parent = next->parent;
      }
      next = parent;
    }
  }
  return {ind, next};
}

template< class T >
TriTreeIt< T > prev(TriTreeIt<T> it)
{
  TriTree<T>* next = it.curr;
  size_t ind = it.s;

  if (!next) {
    return {0, nullptr};
  }

  if (ind) {
    if (next->mid) {
      next = next->mid;
      next = minimum(next);
      ind = 1;
    } else {
      ind = 0;
    }
  } else {
    if (next->lt) {
      next = next->lt;
      next = maximum(next);
      ind = 1;
    } else {
      TriTree<T>* parent = next->parent;
      while (parent) {
        if (parent->rt == next) {
          ind = 1;
          break;
        }
        if (parent->mid == next) {
          ind = 0;
          break;
        }
        next = parent;
        parent = next->parent;
      }
      next = parent;
    }
  }
  return {ind, next};
}

template< class T >
bool hasNext(TriTreeIt<T> it)
{
  return next(it).curr;
}

template< class T >
bool hasPrev(TriTreeIt<T> it)
{
  return prev(it).curr;
}

int main()
{
  TriTree<int>* root = new TriTree<int>{1,2,nullptr,nullptr,nullptr,nullptr};
  TriTreeIt<int> it{0, root};
  while (hasNext(it)) {
    std::cout << value(it) << '\n';
    it = next(it);
  }
  std::cout << value(it) << '\n';
  delete[] root;
}