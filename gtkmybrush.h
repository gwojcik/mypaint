#ifndef __GTK_MY_BRUSH_H__
#define __GTK_MY_BRUSH_H__

#include <glib.h>
#include <glib-object.h>
#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>

#include "surface.h"
#include "brushsettings.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_MY_BRUSH            (gtk_my_brush_get_type ())
#define GTK_MY_BRUSH(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MY_BRUSH, GtkMyBrush))
#define GTK_MY_BRUSH_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_MY_BRUSH, GtkMyBrushClass))
#define GTK_IS_MY_BRUSH(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MY_BRUSH))
#define GTK_IS_MY_BRUSH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_MY_BRUSH))
#define GTK_MY_BRUSH_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_MY_BRUSH, GtkMyBrushClass))


typedef struct _GtkMyBrush       GtkMyBrush;
typedef struct _GtkMyBrushClass  GtkMyBrushClass;

typedef struct {
  // a set of control points (stepwise linear)
  float xvalues[6]; // > 0 because all inputs are > 0
  float yvalues[6]; // range: -oo  .. +oo (added to base_value)
  // xvalues can be zero to indicate that this point is not used.
  // the first point (0, 0) is implicit, would have index -1
} Mapping;
  
typedef struct {
  float base_value;
  // NULL if it does not depend on this input
  Mapping * mapping[INPUT_COUNT];
} Setting;

struct _GtkMyBrush
{
  GObject parent;

  // lowlevevel stuff
  float x, y, pressure, time;
  float dx, dy, dpressure, dtime;
  float dist;
  float actual_radius;

  GtkWidget * queue_draw_widget;

  guchar color[3];

  // misc helpers
  float x_slow, y_slow;
  float dx_slow, dy_slow;
  float last_time;
  float obs__speedabs_slow;
  float rbs__speedabs_slow;

  Setting settings[BRUSH_SETTINGS_COUNT];

};

struct _GtkMyBrushClass
{
  GObjectClass parent_class;
};


GType       gtk_my_brush_get_type   (void) G_GNUC_CONST;
GtkMyBrush* gtk_my_brush_new        (void);

void gtk_my_brush_set_setting (GtkMyBrush * b, int id, float value);
float gtk_my_brush_get_setting (GtkMyBrush * b, int id);

void gtk_my_brush_set_color (GtkMyBrush * b, int red, int green, int blue);

// only for mydrawwidget (not exported to python):
void brush_stroke_to (GtkMyBrush * b, Surface * s, float x, float y, float pressure, float time);
void brush_reset (GtkMyBrush * b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GTK_MY_BRUSH_H__ */
