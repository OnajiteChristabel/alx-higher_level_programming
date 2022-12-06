#ifndef Py_OBJECT_H
#define Py_OBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

/* Object and type object interface */
/*
 * Objects are structures allocated on the heap.  Special rules apply to
 * the use of objects to ensure they are properly garbage-collected.
 * Objects are never allocated statically or on the stack; they must be
 * accessed through special macros and functions only.  (Type objects are
 * exceptions to the first rule; the standard types are represented by
 * statically initialized type objects, although work on type/class unification
 * for Python 2.2 made it possible to have heap-allocated type objects too).
 * An object has a 'reference count' that is increased or decreased when a
 * pointer to the object is copied or deleted; when the reference count
 * reaches zero there are no references to the object left and it can be
 * removed from the heap.
 * An object has a 'type' that determines what it represents and what kind
 * of data it contains.  An object's type is fixed when it is created.
 * Types themselves are represented as objects; an object contains a
 * pointer to the corresponding type object.  The type itself has a type
 * pointer pointing to the object representing the type 'type', which
 * contains a pointer to itself!.Objects do not float around in memory; once allocated an object keeps
 * the same size and address.  Objects that must hold variable-size data
 * can contain pointers to variable-size parts of the object.  Not all
 * objects of the same type have the same size; but the size cannot change
 * after allocation.  (These restrictions are made so a reference to an
 * object can be simply a pointer -- moving an object would require
 * updating all the pointers, and changing an object's size would require
 * moving it if there was another object right next to it.)
 * Objects are always accessed through pointers of the type 'PyObject *'.
 * The type 'PyObject' is a structure that only contains the reference count
 * and the type pointer.  The actual memory allocated for an object
 * contains other data that can only be accessed after casting the pointer
 * to a pointer to a longer structure type.  This longer type must start
 * with the reference count and type fields; the macro PyObject_HEAD should be
 * used for this (to accommodate for future changes).  The implementation
 * of a particular object type can cast the object pointer to the proper
 * type and back.
 * A standard interface exists for objects that contain an array of items
 * whose size is determined when the object is allocated.
 */

#include "pystats.h"

	/* Py_DEBUG implies Py_REF_DEBUG. */
#if defined(Py_DEBUG) && !defined(Py_REF_DEBUG)
#  define Py_REF_DEBUG
#endif
#if defined(Py_LIMITED_API) && defined(Py_TRACE_REFS)
#  error Py_LIMITED_API is incompatible with Py_TRACE_REFS
#endif

#ifdef Py_TRACE_REFS
	/* Define pointers to support a doubly-linked list of all live heap objects. */
#define _PyObject_HEAD_EXTRA            \
	    PyObject *_ob_next;           \
	    PyObject *_ob_prev;

#define _PyObject_EXTRA_INIT _Py_NULL, _Py_NULL,

#else
#  define _PyObject_HEAD_EXTRA
#  define _PyObject_EXTRA_INIT
#endif

	/* PyObject_HEAD defines the initial segment of every PyObject. */
#define PyObject_HEAD                   PyObject ob_base;

#define PyObject_HEAD_INIT(type)        \
	    { _PyObject_EXTRA_INIT              \
		        1, (type) },

#define PyVarObject_HEAD_INIT(type, size)       \
	    { PyObject_HEAD_INIT(type) (size) },
/* PyObject_VAR_HEAD defines the initial segment of all variable-size
 *  * container objects.  These end with a declaration of an array with 1
 *   * element, but enough space is malloc'ed so that the array actually
 *    * has room for ob_size elements.  Note that ob_size is an element count,
 *     * not necessarily a byte count.
 *      */
#define PyObject_VAR_HEAD      PyVarObject ob_base;
#define Py_INVALID_SIZE (Py_ssize_t)-1
/* Nothing is actually declared to be a PyObject, but every pointer to
 *  * a Python object can be cast to a PyObject*.  This is inheritance built
 *   * by hand.  Similarly every pointer to a variable-size Python object can,
 *    * in addition, be cast to PyVarObject*.
 *     */
	struct _object {
		    _PyObject_HEAD_EXTRA
			        Py_ssize_t ob_refcnt;
		        PyTypeObject *ob_type;
	};

/* Cast argument to PyObject* type. */
#define _PyObject_CAST(op) _Py_CAST(PyObject*, (op))
// Test if the 'x' object is the 'y' object, the same as "x is y" in Python.
PyAPI_FUNC(int) Py_Is(PyObject *x, PyObject *y);
#define Py_Is(x, y) ((x) == (y))
static inline Py_ssize_t Py_REFCNT(PyObject *ob) {
	    return ob->ob_refcnt;
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define Py_REFCNT(ob) Py_REFCNT(_PyObject_CAST(ob))
#endif
// bpo-39573: The Py_SET_TYPE() function must be used to set an object type.
static inline PyTypeObject* Py_TYPE(PyObject *ob) {
return ob->ob_type;
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define Py_TYPE(ob) Py_TYPE(_PyObject_CAST(ob))
#endif

// bpo-39573: The Py_SET_SIZE() function must be used to set an object size.
static inline Py_ssize_t Py_SIZE(PyObject *ob) {
	    PyVarObject *var_ob = _PyVarObject_CAST(ob);
	        return var_ob->ob_size;
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define Py_SIZE(ob) Py_SIZE(_PyObject_CAST(ob))
#endif

static inline int Py_IS_TYPE(PyObject *ob, PyTypeObject *type) {
	    return Py_TYPE(ob) == type;
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define Py_IS_TYPE(ob, type) Py_IS_TYPE(_PyObject_CAST(ob), (type))
#endif

static inline void Py_SET_REFCNT(PyObject *ob, Py_ssize_t refcnt) {
	    ob->ob_refcnt = refcnt;
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define Py_SET_REFCNT(ob, refcnt) Py_SET_REFCNT(_PyObject_CAST(ob), (refcnt))
#endif

static inline void Py_SET_TYPE(PyObject *ob, PyTypeObject *type) {
	    ob->ob_type = type;
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define Py_SET_TYPE(ob, type) Py_SET_TYPE(_PyObject_CAST(ob), type)
#endif

static inline void Py_SET_SIZE(PyVarObject *ob, Py_ssize_t size) {
	    ob->ob_size = size;
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define Py_SET_SIZE(ob, size) Py_SET_SIZE(_PyVarObject_CAST(ob), (size))
#endif
/*
 Type objects contain a string containing the type name (to help somewhat
 in debugging), the allocation parameters (see PyObject_New() and
 PyObject_NewVar()),
 and methods for accessing objects of the type.  Methods are optional, a
 nil pointer meaning that particular kind of access is not available for
 this type.  The Py_DECREF() macro uses the tp_dealloc method without
 checking for a nil pointer; it should always be implemented except if
 the implementation can guarantee that the reference count will never
 reach zero (e.g., for statically allocated type objects).
NB: the methods for certain type groups are now contained in separate
method blocks.
*/
typedef PyObject * (*unaryfunc)(PyObject *);
typedef PyObject * (*binaryfunc)(PyObject *, PyObject *);
typedef PyObject * (*ternaryfunc)(PyObject *, PyObject *, PyObject *);
typedef int (*inquiry)(PyObject *);
typedef Py_ssize_t (*lenfunc)(PyObject *);
typedef PyObject *(*ssizeargfunc)(PyObject *, Py_ssize_t);
typedef PyObject *(*ssizessizeargfunc)(PyObject *, Py_ssize_t, Py_ssize_t);
typedef int(*ssizeobjargproc)(PyObject *, Py_ssize_t, PyObject *);
typedef int(*ssizessizeobjargproc)(PyObject *, Py_ssize_t, Py_ssize_t, PyObject *);
typedef int(*objobjargproc)(PyObject *, PyObject *, PyObject *);

typedef int (*objobjproc)(PyObject *, PyObject *);
typedef int (*visitproc)(PyObject *, void *);
typedef int (*traverseproc)(PyObject *, visitproc, void *);
typedef void (*freefunc)(void *);
typedef void (*destructor)(PyObject *);
typedef PyObject *(*getattrfunc)(PyObject *, char *);
typedef PyObject *(*getattrofunc)(PyObject *, PyObject *);
typedef int (*setattrfunc)(PyObject *, char *, PyObject *);
typedef int (*setattrofunc)(PyObject *, PyObject *, PyObject *);
typedef PyObject *(*reprfunc)(PyObject *);
typedef Py_hash_t (*hashfunc)(PyObject *);
typedef PyObject *(*richcmpfunc) (PyObject *, PyObject *, int);
typedef PyObject *(*getiterfunc) (PyObject *);
typedef PyObject *(*iternextfunc) (PyObject *);
typedef PyObject *(*descrgetfunc) (PyObject *, PyObject *, PyObject *);
typedef int (*descrsetfunc) (PyObject *, PyObject *, PyObject *);
typedef int (*initproc)(PyObject *, PyObject *, PyObject *);
typedef PyObject *(*newfunc)(PyTypeObject *, PyObject *, PyObject *);
typedef PyObject *(*allocfunc)(PyTypeObject *, Py_ssize_t);

if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 >= 0x030c0000 // 3.12
typedef PyObject *(*vectorcallfunc)(PyObject *callable, PyObject *const *args,
		                                    size_t nargsf, PyObject *kwnames);
#endif

typedef struct{
	    int slot;    /* slot id, see below */
	        void *pfunc; /* function pointer */
} PyType_Slot;
typedef struct{
	    const char* name;
	        int basicsize;
		    int itemsize;
		        unsigned int flags;
			    PyType_Slot *slots; /* terminated by slot==0. */
} PyType_Spec;

PyAPI_FUNC(PyObject*) PyType_FromSpec(PyType_Spec*);
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 >= 0x03030000
PyAPI_FUNC(PyObject*) PyType_FromSpecWithBases(PyType_Spec*, PyObject*);
#endif
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 >= 0x03040000
PyAPI_FUNC(void*) PyType_GetSlot(PyTypeObject*, int);
#endif
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 >= 0x03090000
PyAPI_FUNC(PyObject*) PyType_FromModuleAndSpec(PyObject *, PyType_Spec *, PyObject *);
PyAPI_FUNC(PyObject *) PyType_GetModule(PyTypeObject *);
PyAPI_FUNC(void *) PyType_GetModuleState(PyTypeObject *);
#endif
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 >= 0x030B0000
PyAPI_FUNC(PyObject *) PyType_GetName(PyTypeObject *);
PyAPI_FUNC(PyObject *) PyType_GetQualName(PyTypeObject *);
#endif
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 >= 0x030C0000
PyAPI_FUNC(PyObject *) PyType_FromMetaclass(PyTypeObject*, PyObject*, PyType_Spec*, PyObject*);
#endif

/* Generic type check */
PyAPI_FUNC(int) PyType_IsSubtype(PyTypeObject *, PyTypeObject *);

static inline int PyObject_TypeCheck(PyObject *ob, PyTypeObject *type) {
	    return Py_IS_TYPE(ob, type) || PyType_IsSubtype(Py_TYPE(ob), type);
}
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  define PyObject_TypeCheck(ob, type) PyObject_TypeCheck(_PyObject_CAST(ob), (type))
#endif

PyAPI_DATA(PyTypeObject) PyType_Type; /* built-in 'type' */
PyAPI_DATA(PyTypeObject) PyBaseObject_Type; /* built-in 'object' */
PyAPI_DATA(PyTypeObject) PySuper_Type; /* built-in 'super' */

PyAPI_FUNC(unsigned long) PyType_GetFlags(PyTypeObject*);

PyAPI_FUNC(int) PyType_Ready(PyTypeObject *);
PyAPI_FUNC(PyObject *) PyType_GenericAlloc(PyTypeObject *, Py_ssize_t);
PyAPI_FUNC(PyObject *) PyType_GenericNew(PyTypeObject *,
		                                               PyObject *, PyObject *);
PyAPI_FUNC(unsigned int) PyType_ClearCache(void);
PyAPI_FUNC(void) PyType_Modified(PyTypeObject *);

