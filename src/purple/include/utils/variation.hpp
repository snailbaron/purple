#pragma once

/**
 * Variation -- multiple sets of related user-defined types.
 *
 * Notes on terminology
 * --------------------
 *
 * The words 'Variation', 'Category', and 'Type' used here are specific to this
 * code, and are not to be confused with broader terms of C++ or general
 * programming (this is especially concerning the word 'Type'). To avoid
 * confusion, these specific terms are capitalized.
 *
 * 1. Theoretical description
 * ---------------------------
 *
 * Variation is a basic template that allows the user to create certain types,
 * called variation implementations.
 *
 * Each such type is said to belong to a Category, and to have a Type. Variation
 * implementations of the same Category (and different Types) are represented by
 * types that are somehow related. User may wish to work with same Category
 * variation implementations without knowing their Types. Variation
 * implementations belonging to different Categories are not related in any way,
 * and are always managed separately.
 *
 * 2. Technical details
 * --------------------
 *
 * A Variation is characterized by Category and Type.
 * - Category is an enumeration type, storing all possible Types for Variations
 *   belonging to this Category.
 * - Type is a value of Category type.
 *
 * Each <Category, Type> combination is represented by a user-defined type in
 * code. This user-defined type is the variation implementation for this Type of
 * this Category.
 *
 * There is no such thing as a Variation belonging to an unknown Category. When
 * referencing Variations in your code, you always specify a certain Category.
 * There is, however, a way to work with a Variation of a certain Category
 * without knowing its Type.
 *
 * 3. Class definitions
 * --------------------
 *
 * The Variation infrastructure uses the following class hierarchy to represent
 * Variations and variation implementations:
 *
 *                           Variation<Category>
 *                                   |
 *                       NewVariation<Category, Type>
 *                                   |
 *                       `variation implementation`
 *
 * Variation<Category>:
 *     Base class of any Variation belonging to Category. User code working with
 *     Variations belonging to Category without knowing their types should use
 *     this class.
 *
 *     Variation<Category> knows its Type, passed at runtime. User code may use
 *     this to convert such variation to appropriate variation implementation
 *     type.
 *
 * NewVariation<Category, Type>:
 *     A helper class that known both its Category and Type at compilation time.
 *     Variation implementations should derive from this class directly.
 *
 *     This class provides a default constructor for variation implementations.
 *     Such constructor will initialize Variation<Category> with correct Type
 *     at runtime. This way, the binding between a variation implementation and
 *     a Type is performed with inheritance, not inside variation
 *     implementation's body.
 *
 *     Additionally, this class provides a convenient 'staticType' member value
 *     (alias of Type), which may be used in variation implementation.
 *
 * In addition to the Variation class hierarchy, VariationOfTypeHolder template
 * defines a 'Type' alias, which allows to get the variation implementation type
 * for a certain (Category, Value) pair. Each variation implementation is
 * required to "register" itself for appropriate Category and Type, with a
 * specialization of this template.
 *
 * For more convenient use, there is a helper VariationOf template, which may
 * be used in the following way:
 *     using VariationImplementationType = VariationOf<MyCategory, MyType>;
 *
 * To sum up, to create a new variation implementation, you would need to:
 * - Have your Category defined as an enumeration type, storing all required
 *   Types.
 * - Define your variation implementation struct, inheriting from
 *   NewVariation<Category, Type>
 * - Register your variation implementation by providing a VariationOfTypeHolder
 *   specialization, storing a 'Type' alias to your variation implementation
 *   type.
 *
 * To make this easier, there is a helper macro, NEW_VARIATION. Assuming that
 * MyCategory is an 'enum class' storing your types, this macro may be used in
 * the following way:
 *     NEW_VARIATION(MyImplementation, MyCategory, MyCategory::MyType) {
 *         ...body of your implementation...
 *     };
 *
 * 4. How to define a new category
 * -------------------------------
 *
 * As different Categories represent completely unrelated entities, you would
 * probably want to name Variations of a certain Category in a more
 * understandable way. The usual way to do this is described below.
 *
 * Let's assume we want to define events of different types, and implement each
 * event with a struct. We decide to implement them using the Variations
 * infrastructure.
 *
 * This is the usual sequence of steps you need to achieve that:
 *
 *   - Create an enumeration to store all event types:
 *         enum class EventType {
 *             EventTypeOne,
 *             EventTypeTwo,
 *         };
 *
 *   - Define a convenient alias for Variations of your category. This alias
 *     will probably be used in user code, dealing with events which type is
 *     unknown.
 *         using Event = Variation<EventType>;
 *
 *   - Define a convenient alias for VariationOf helper template. Again, this is
 *     what will be used in user code, when we want to get certain event
 *     implementation having an event type.
 *         template <EventType ET>
 *         using EventOf = typename VariationOf<EventType, ET>;
 *
 *   - Consider defining another macro, to replace NEW_VARIATION. For events,
 *     you could use:
 *         #define NEW_EVENT(NAME, TYPE) NEW_VARIATION(NAME, EventType, TYPE)
 *
 * After these simple steps, you could define a new event by:
 *   - Adding a new value to EventType enumeration
 *   - Implementing event's body under a macro:
 *         NEW_EVENT(OneEvent, EventType::EventTypeOne) {
 *             ...some event data...
 *         };
 *
 * Note that you completely control the body of your event.
 */

#include <type_traits>

template <class VT>
struct Variation {
    static_assert(std::is_enum<VT>::value,
        "Variation: template parameter must be enumeration type");

    explicit Variation(VT type) : type(type) {}
    VT type;
};

template <class VT, VT Type>
struct NewVariation : Variation<VT> {
    NewVariation() : Variation<VT>(Type) {}
    static const VT staticType = Type;
};

template <class VT, VT type>
struct VariationOfTypeHolder;

template <class VT, VT type>
using VariationOf = typename VariationOfTypeHolder<VT, type>::Type;

#define NEW_VARIATION(NAME, CATEGORY, TYPE)                         \
    struct NAME;                                                    \
    template <> struct VariationOfTypeHolder<CATEGORY, TYPE> {      \
        using Type = NAME;                                          \
    };                                                              \
    struct NAME : NewVariation<CATEGORY, TYPE>

#define IMPLEMENT_VARIATION(NAME, TYPE_ENUM)                                \
    using NAME = Variation<TYPE_ENUM>;                                      \
                                                                            \
    template <TYPE_ENUM Provided ## TYPE_ENUM>                              \
    using NAME ## Of =                                                      \
        typename VariationOf<TYPE_ENUM, Provided ## TYPE_ENUM>;