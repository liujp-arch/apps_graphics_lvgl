/**
 * @file lv_obj_scroll.h
 *
 */

#ifndef LV_OBJ_SCROLL_H
#define LV_OBJ_SCROLL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_area.h"
#include "../misc/lv_anim.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Can't include lv_obj.h because it includes this header file */
struct _lv_obj_t;

/** Scrollbar modes: shows when should the scrollbars be visible*/
enum {
    LV_SCROLLBAR_MODE_OFF,      /**< Never show scrollbars*/
    LV_SCROLLBAR_MODE_ON,       /**< Always show scrollbars*/
    LV_SCROLLBAR_MODE_ACTIVE,   /**< Show scroll bars when object is being scrolled*/
    LV_SCROLLBAR_MODE_AUTO,     /**< Show scroll bars when the content is large enough to be scrolled*/
};
typedef uint8_t lv_scrollbar_mode_t;


/** Scroll span align options. Tells where to align the snapable children when scroll stops. */
enum {
    LV_SCROLL_SNAP_NONE,    /**< Do not align, leave where it is */
    LV_SCROLL_SNAP_START,   /**< Align to to the left/top */
    LV_SCROLL_SNAP_END,     /**< Align to to the right/bottom */
    LV_SCROLL_SNAP_CENTER   /**< Align to to the center */
};
typedef uint8_t lv_scroll_snap_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Setter functions
 *====================*/

/**
 * Set how the scrollbars should behave.
 * @param obj       pointer to an object
 * @param mode      LV_SCROLL_MODE_ON/OFF/AUTO/ACTIVE
 */
void lv_obj_set_scrollbar_mode(struct _lv_obj_t * obj, lv_scrollbar_mode_t mode);

/**
 * Set the object in which directions can be scrolled
 * @param obj       pointer to an object
 * @param dir       the allow scroll directions. An element or OR-ed values of `lv_dir_t`
 */
void lv_obj_set_scroll_dir(struct _lv_obj_t * obj, lv_dir_t dir);

/**
 * Set where to snap the children when scrolling ends horizontally
 * @param obj       pointer to an object
 * @param align     the snap align to set from `lv_snap_align_t`
 */
void lv_obj_set_scroll_snap_x(struct _lv_obj_t * obj, lv_scroll_snap_t align);

/**
 * Set where to snap the children when scrolling ends vertically
 * @param obj       pointer to an object
 * @param align     the snap align to set from `lv_snap_align_t`
 */
void lv_obj_set_scroll_snap_y(struct _lv_obj_t * obj, lv_scroll_snap_t align);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the current scroll mode (when to hide the scrollbars)
 * @param obj       pointer to an object
 * @return          the current scroll mode from `lv_scroll_mode_t`
 */
lv_scrollbar_mode_t lv_obj_get_scrollbar_mode(const struct _lv_obj_t * obj);

/**
 * Get the object in which directions can be scrolled
 * @param obj       pointer to an object
 * @param dir       the allow scroll directions. An element or OR-ed values of `lv_dir_t`
 */
lv_dir_t lv_obj_get_scroll_dir(const struct _lv_obj_t * obj);

/**
 * Get where to snap the children when scrolling ends horizontally
 * @param obj       pointer to an object
 * @return          the current snap align from `lv_snap_align_t`
 */
lv_scroll_snap_t lv_obj_get_scroll_snap_x(const struct _lv_obj_t * obj);

/**
 * Get where to snap the children when scrolling ends vertically
 * @param  obj      pointer to an object
 * @return          the current snap align from `lv_snap_align_t`
 */
lv_scroll_snap_t lv_obj_get_scroll_snap_y(const struct _lv_obj_t * obj);

/**
 * Get current X scroll position.
 * @param obj       pointer to an object
 * @return          the current scroll position from the left edge.
 *                  If the object is not scrolled return 0
 *                  If scrolled return > 0
 *                  If scrolled in (elastic scroll) return < 0
 */
lv_coord_t lv_obj_get_scroll_x(const struct _lv_obj_t * obj);

/**
 * Get current Y scroll position.
 * @param obj       pointer to an object
 * @return          the current scroll position from the top edge.
 *                  If the object is not scrolled return 0
 *                  If scrolled return > 0
 *                  If scrolled inside return < 0
 */
lv_coord_t lv_obj_get_scroll_y(const struct _lv_obj_t * obj);

/**
 * Return the height of the area above the object.
 * That is the number of pixels the object can be scrolled down.
 * Normally positive but can be negative when scrolled inside.
 * @param obj       pointer to an object
 * @return          the scrollable area above the object in pixels
 */
lv_coord_t lv_obj_get_scroll_top(struct _lv_obj_t * obj);

/**
 * Return the height of the area below the object.
 * That is the number of pixels the object can be scrolled down.
 * Normally positive but can be negative when scrolled inside.
 * @param obj       pointer to an object
 * @return          the scrollable area below the object in pixels
 */
lv_coord_t lv_obj_get_scroll_bottom(struct _lv_obj_t * obj);

/**
 * Return the width of the area on the left the object.
 * That is the number of pixels the object can be scrolled down.
 * Normally positive but can be negative when scrolled inside.
 * @param obj       pointer to an object
 * @return          the scrollable area on the left the object in pixels
 */
lv_coord_t lv_obj_get_scroll_left(struct _lv_obj_t * obj);

/**
 * Return the width of the area on the right the object.
 * That is the number of pixels the object can be scrolled down.
 * Normally positive but can be negative when scrolled inside.
 * @param obj       pointer to an object
 * @return          the scrollable area on the right the object in pixels
 */
lv_coord_t lv_obj_get_scroll_right(struct _lv_obj_t * obj);

/**
 * Get the X and Y coordinates where the scrolling will end for this object if a scrolling animation is in progress.
 * In no scrolling animation give the current `x` or `y` scroll position.
 * @param obj       pointer to an object
 * @param           end poinr to point to store the result
 */
void lv_obj_get_scroll_end(struct _lv_obj_t  * obj, lv_point_t * end);

/*=====================
 * Other functions
 *====================*/

/**
 *
 * Scroll by a given amount of pixels
 * @param obj       pointer to an object to scroll
 * @param x         pixels to scroll horizontally
 * @param y         pixels to scroll vertically
 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
 * @note            > 0 value means scroll right/bottom (show the more content on the right/bottom)
 * @note
 */
void lv_obj_scroll_by(struct _lv_obj_t * obj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en);

/**
 * Scroll to a given coordinate on an object.
 * `x` and `y` will be limited internally to allow scrolling only on the content area.
 * @param obj       pointer to an object to scroll
 * @param x         pixels to scroll horizontally
 * @param y         pixels to scroll vertically
 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
 */
void lv_obj_scroll_to(struct _lv_obj_t * obj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en);

/**
 * Scroll to a given X coordinate on an object.
 * `x` will be limited internally to allow scrolling only on the content area.
 * @param obj       pointer to an object to scroll
 * @param x         pixels to scroll horizontally
 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
 */
void lv_obj_scroll_to_x(struct _lv_obj_t * obj, lv_coord_t x, lv_anim_enable_t anim_en);

/**
 * Scroll to a given Y coordinate on an object
 * `y` will be limited internally to allow scrolling only on the content area.
 * @param obj       pointer to an object to scroll
 * @param y         pixels to scroll vertically
 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
 */
void lv_obj_scroll_to_y(struct _lv_obj_t * obj, lv_coord_t y, lv_anim_enable_t anim_en);

/**
 * Scroll to an object until it becomes visible on its parent
 * @param obj       pointer to an object to scroll into view
 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
 */
void lv_obj_scroll_to_view(struct _lv_obj_t * obj, lv_anim_enable_t anim_en);

/**
 * Scroll to an object until it becomes visible on its parent.
 * Do the same on the parent's parent, and so on.
 * Therefore the object will be scrolled into view even it has nested scrollable parents
 * @param obj       pointer to an object to scroll into view
 * @param anim_en   LV_ANIM_ON: scroll with animation; LV_ANIM_OFF: scroll immediately
 */
void lv_obj_scroll_to_view_recursive(struct _lv_obj_t * obj, lv_anim_enable_t anim_en);

/**
 * Tell whether an object is being scrolled or not at this moment
 * @param obj   pointer to an object
 * @return      true: `obj` is being scrolled
 */
bool lv_obj_is_scrolling(const struct _lv_obj_t * obj);

/**
 * Check the children of `obj` and scroll `obj` to fulfill the scroll_snap settings
 * @param obj       an object whose children needs to checked and snapped
 * @param anim_en   LV_ANIM_ON/OFF
 */
void lv_obj_update_snap(struct _lv_obj_t * obj, lv_anim_enable_t anim_en);

/**
 * Get the area of the scrollbars
 * @param obj       pointer to an object
 * @param hor_area  pointer to store the area of the horizontal scrollbar
 * @param ver_area  pointer to store the area of the vertical  scrollbar
 */
void lv_obj_get_scrollbar_area(struct _lv_obj_t * obj, lv_area_t * hor, lv_area_t * ver);

/**
 * Invalidate the area of the scrollbars
 * @param obj       pointer to an object
 */
void lv_obj_scrollbar_invalidate(struct _lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_OBJ_SCROLL_H*/
