// Generated by CoffeeScript 1.7.1
(function() {
  var AALine, Dim, Pos, Rand, Rect, build_graph, clear, draw_corridor, draw_rect, draw_rects, find_closest, generate_rects, init, inside, intersect, randn, random_int, rng, seed, shuffle;

  Rand = (function() {
    function Rand(seed) {
      this.seed = seed;
      this.multiplier = 1664525;
      this.modulo = 4294967296;
      this.offset = 1013904223;
      if (!((this.seed != null) && (0 <= seed && seed < this.modulo))) {
        this.seed = (new Date().valueOf() * new Date().getMilliseconds()) % this.modulo;
      }
    }

    Rand.prototype.seed = function(seed) {
      return this.seed = seed;
    };

    Rand.prototype.randn = function() {
      return this.seed = (this.multiplier * this.seed + this.offset) % this.modulo;
    };

    Rand.prototype.randf = function() {
      return this.randn() / this.modulo;
    };

    Rand.prototype.rand = function(n) {
      return Math.floor(this.randf() * n);
    };

    Rand.prototype.rand2 = function(min, max) {
      return min + this.rand(max - min);
    };

    return Rand;

  })();

  Pos = (function() {
    function Pos(x, y) {
      this.x = x;
      this.y = y;
    }

    Pos.prototype.plus = function(dim) {
      return new Pos(this.x + dim.w, this.y + dim.h);
    };

    Pos.prototype.minus = function(dim) {
      return new Pos(this.x - dim.w, this.y - dim.h);
    };

    return Pos;

  })();

  Dim = (function() {
    function Dim(w, h) {
      this.w = w;
      this.h = h;
    }

    return Dim;

  })();

  AALine = (function() {
    function AALine(p1, p2) {
      var _ref, _ref1;
      this.p1 = p1;
      this.p2 = p2;
      if (this.p1.x === this.p2.x) {
        if (this.p2.y < this.p1.y) {
          _ref = [this.p2, this.p1], this.p1 = _ref[0], this.p2 = _ref[1];
          return;
        }
      }
      if (this.p1.y === this.p2.y) {
        if (this.p2.x < this.p1.x) {
          _ref1 = [this.p2, this.p1], this.p1 = _ref1[0], this.p2 = _ref1[1];
          return;
        }
      }
    }

    return AALine;

  })();

  Rect = (function() {
    function Rect(pos, dim) {
      this.pos = pos;
      this.dim = dim;
      this.adj = [];
    }

    Rect.prototype.top = function() {
      return new AALine(this.pos, new Pos(this.pos.x + this.dim.w, this.pos.y));
    };

    Rect.prototype.right = function() {
      return new AALine(new Pos(this.pos.x + this.dim.w, this.pos.y), new Pos(this.pos.x + this.dim.w, this.pos.y + this.dim.h));
    };

    Rect.prototype.bottom = function() {
      return new AALine(this.pos.plus(this.dim), new Pos(this.pos.x, this.pos.y + this.dim.h));
    };

    Rect.prototype.left = function() {
      return new AALine(new Pos(this.pos.x, this.pos.y + this.dim.h), this.pos);
    };

    Rect.prototype.clip = function(other) {
      var oldx, oldy;
      if (inside(other.pos, this) && inside(other.pos.plus(other.dim), this)) {
        this.dim.w = other.pos.x - this.pos.x - 1;
        this.adj.push(other);
      }
      if (intersect(this.top(), other)) {
        oldy = this.pos.y;
        this.pos.y = other.pos.y + other.dim.h + 1;
        this.dim.h -= this.pos.y - oldy;
        this.adj.push(other);
      }
      if (intersect(this.right(), other)) {
        this.dim.w = other.pos.x - 1 - this.pos.x;
        this.adj.push(other);
      }
      if (intersect(this.bottom(), other)) {
        this.dim.h = other.pos.y - 1 - this.pos.y;
        this.adj.push(other);
      }
      if (intersect(this.left(), other)) {
        oldx = this.pos.x;
        this.pos.x = other.pos.x + other.dim.w + 1;
        this.dim.w -= this.pos.x - oldx;
        return this.adj.push(other);
      }
    };

    return Rect;

  })();

  inside = function(point, rect) {
    return point.x >= rect.pos.x && point.x <= rect.pos.x + rect.dim.w && point.y >= rect.pos.y && point.y <= rect.pos.y + rect.dim.h;
  };

  intersect = function(line, rect) {
    return line.p2.x >= rect.pos.x && line.p1.x <= rect.pos.x + rect.dim.w && line.p1.y <= rect.pos.y + rect.dim.h && line.p2.y >= rect.pos.y;
  };

  seed = new Rand().randn();

  console.log("seed: " + seed);

  rng = new Rand(seed);

  randn = function() {
    return rng.randn();
  };

  random_int = function(a, b) {
    return a + randn() % (b - a + 1);
  };

  shuffle = function(a) {
    var i, j, _i, _ref, _ref1;
    for (i = _i = _ref = a.length - 1; _ref <= 1 ? _i <= 1 : _i >= 1; i = _ref <= 1 ? ++_i : --_i) {
      j = random_int(0, i);
      _ref1 = [a[j], a[i]], a[i] = _ref1[0], a[j] = _ref1[1];
    }
    return a;
  };

  generate_rects = function(ctx, width, height) {
    var h, i, other, rect, rects, w, wellformed, x, y, _i, _j, _len;
    rects = [];
    for (i = _i = 1; _i <= 100; i = ++_i) {
      x = random_int(0, 100);
      y = random_int(0, 75);
      w = Math.min(random_int(10, 40), 100 - x);
      h = Math.min(random_int(10, 40), 75 - y);
      rect = new Rect(new Pos(x, y), new Dim(w, h));
      wellformed = true;
      for (_j = 0, _len = rects.length; _j < _len; _j++) {
        other = rects[_j];
        rect.clip(other);
        wellformed = rect.dim.w > 2 && rect.dim.h > 2;
        if (!wellformed) {
          break;
        }
      }
      if (wellformed) {
        rects.push(rect);
      }
    }
    return rects;
  };

  find_closest = function(graph, nodes) {
    var min_length, n1, n2, ret, _i, _j, _len, _len1;
    ret = void 0;
    min_length = Infinity;
    for (_i = 0, _len = graph.length; _i < _len; _i++) {
      n1 = graph[_i];
      for (_j = 0, _len1 = nodes.length; _j < _len1; _j++) {
        n2 = nodes[_j];
        if (distance(n1, n2) < min_length) {
          ret = n2;
        }
      }
    }
    return ret;
  };

  build_graph = function(rects) {
    var closest, graph, rect, _i, _len, _results;
    graph = [];
    _results = [];
    for (_i = 0, _len = rects.length; _i < _len; _i++) {
      rect = rects[_i];
      graph.push(rect);
      _results.push(closest = find_closest(rect, rects));
    }
    return _results;
  };

  draw_rect = function(ctx, tilesize, rect, color) {
    ctx.fillStyle = color != null ? color : "#883";
    ctx.fillRect(tilesize * rect.pos.x, tilesize * rect.pos.y, tilesize * rect.dim.w, tilesize * rect.dim.h);
    if (rect.dim.w === 1 || rect.dim.h === 1) {
      return;
    }
    ctx.fillStyle = "#000";
    return ctx.fillRect(tilesize * (rect.pos.x + 1), tilesize * (rect.pos.y + 1), tilesize * (rect.dim.w - 2), tilesize * (rect.dim.h - 2));
  };

  clear = function(ctx, color) {
    ctx.fillStyle = color != null ? color : "#aaa";
    return ctx.fillRect(0, 0, canvas.width, canvas.height);
  };

  draw_rects = function(ctx, tilesize, width, height, rects) {
    var canvas, gridsize, random_color, rect, set_tile, _i, _len, _results;
    canvas = ctx.canvas;
    gridsize = new Dim(canvas.width / tilesize, canvas.height / tilesize);
    console.log("grid: " + gridsize.w + " x " + gridsize.h);
    clear(ctx);
    set_tile = function(x, y, color) {
      ctx.fillStyle = color != null ? color : "#883";
      return ctx.fillRect(tilesize * x, tilesize * y, tilesize, tilesize);
    };
    random_color = function() {
      var r;
      r = [random_int(0, 255), 255, 0];
      shuffle(r);
      return "rgb(" + r[0] + "," + r[1] + "," + r[2] + ")";
    };
    _results = [];
    for (_i = 0, _len = rects.length; _i < _len; _i++) {
      rect = rects[_i];
      _results.push(draw_rect(ctx, tilesize, rect, '#883'));
    }
    return _results;
  };


  /*
   * draw a corridor from point 'p1' to point 'p2'
   * with at most one bend in the middle, open at each end to connect rooms
   * 'thickness' wide total, leaving
   * 'inner_thickness' space between sides,
   * 'flipped' determines in which direction the corridor bends,
   * following the x or y axis first, respectively
   */

  draw_corridor = function(ctx, tilesize, p1, p2, thickness, inner_thickness, flipped) {
    var close, dir, dir1, dir2, end, fill_rect, mid, set_tile, sign, start;
    flipped = flipped != null ? flipped : false;
    start = p1;
    mid = void 0;
    if (flipped) {
      mid = new Pos(p1.x, p2.y);
    } else {
      mid = new Pos(p2.x, p1.y);
    }
    end = p2;

    /*
    	 * Helper function to fill a rectangle spanned by two points
    	 * d is the diameter. If the diameter is even, this results
    	 * in an asymmetric shape.
     */
    fill_rect = function(a, b, d, color) {
      var h, w, x1, x2, y1, y2, _ref, _ref1;
      _ref = a.x < b.x ? [a.x, b.x] : [b.x, a.x], x1 = _ref[0], x2 = _ref[1];
      _ref1 = a.y < b.y ? [a.y, b.y] : [b.y, a.y], y1 = _ref1[0], y2 = _ref1[1];
      w = x2 - x1;
      h = y2 - y1;
      ctx.fillStyle = color;
      return ctx.fillRect(tilesize * (x1 - Math.floor(d / 2)), tilesize * (y1 - Math.floor(d / 2)), tilesize * (w + d), tilesize * (h + d));
    };
    set_tile = function(x, y, color) {
      return fill_rect(new Pos(x, y), new Pos(x, y), 1, color != null ? color : '#0ff');
    };
    sign = function(x) {
      if (x < 0) {
        return -1;
      } else if (close(x, 0)) {
        return 0;
      } else {
        return 1;
      }
    };
    close = function(x, y) {
      return Math.abs(x - y) < 0.001;
    };
    if (close(mid.y, start.y)) {
      dir1 = new Dim(sign(mid.x - start.x), 0);
    } else {
      dir1 = new Dim(0, sign(mid.y - start.y));
    }
    if (close(mid.y, end.y)) {
      dir2 = new Dim(sign(mid.x - end.x), 0);
    } else {
      dir2 = new Dim(0, sign(mid.y - end.y));
    }

    /*
    	 * horizontal or vertical paths without mid have only one rect
    	 * all other paths consist of two rects
    	 * cut off one tile on the side leading into and out of the corridor,
    	 * respectively
     */
    if (close(end.x, start.x) || close(end.y, start.y)) {
      if (close(end.x, start.x)) {
        dir = new Dim(0, sign(end.y - start.y));
      } else {
        dir = new Dim(sign(end.x - start.x), 0);
      }
      fill_rect(start.plus(dir), end.minus(dir), thickness, '#f00');
    } else {
      fill_rect(start.plus(dir1), mid, thickness, '#080');
      fill_rect(mid, end.plus(dir2), thickness, '#808');
    }
    fill_rect(start, mid, inner_thickness, '#ff0');
    fill_rect(mid, end, inner_thickness, '#ff0');
    set_tile(p1.x, p1.y, '#0f0');
    return set_tile(p2.x, p2.y, '#f0f');
  };

  init = function() {
    var canvas, ctx, highlight_rect, inner_label, inner_slider, mouse_pos, outer_label, outer_slider, rects, redraw, tilesize, tilesize_label, tilesize_slider;
    canvas = document.getElementById('canvas');
    ctx = canvas.getContext('2d');
    rects = generate_rects();
    outer_slider = document.getElementById('outer');
    outer_label = document.getElementById('outer_label');
    inner_slider = document.getElementById('inner');
    inner_label = document.getElementById('inner_label');
    tilesize_slider = document.getElementById('tilesize');
    tilesize_label = document.getElementById('tilesize_label');
    tilesize = function() {
      return tilesize_slider.value;
    };
    mouse_pos = function(event) {
      var rect;
      rect = canvas.getBoundingClientRect();
      return new Pos(Math.floor((event.clientX - rect.left) / tilesize()), Math.floor((event.clientY - rect.top) / tilesize()));
    };
    redraw = function(event) {
      clear(ctx);
      draw_corridor(ctx, tilesize(), new Pos(5, 5), new Pos(15, 2), Math.floor(outer_slider.value), Math.floor(inner_slider.value), false);
      return draw_corridor(ctx, tilesize(), new Pos(25, 25), mouse_pos(event), Math.floor(outer_slider.value), Math.floor(inner_slider.value), event.shiftKey);
    };
    highlight_rect = function(event) {
      var neighbor, rect, _i, _len, _results;
      draw_rects(ctx, tilesize(), 800, 600, rects);
      _results = [];
      for (_i = 0, _len = rects.length; _i < _len; _i++) {
        rect = rects[_i];
        if (inside(mouse_pos(event), rect)) {
          draw_rect(ctx, tilesize(), rect, '#f00');
          _results.push((function() {
            var _j, _len1, _ref, _results1;
            _ref = rect.adj;
            _results1 = [];
            for (_j = 0, _len1 = _ref.length; _j < _len1; _j++) {
              neighbor = _ref[_j];
              _results1.push(draw_rect(ctx, tilesize(), rect.neighbor, '#0f0'));
            }
            return _results1;
          })());
        } else {
          _results.push(void 0);
        }
      }
      return _results;
    };
    canvas.addEventListener('mousemove', redraw);
    canvas.addEventListener('keydown', redraw);
    outer_slider.addEventListener('input', function(event) {
      outer_label.innerHTML = outer.value;
      return redraw(event);
    });
    inner_slider.addEventListener('input', function(event) {
      inner_label.innerHTML = inner.value;
      return redraw(event);
    });
    return tilesize_slider.addEventListener('input', function(event) {
      tilesize_label.innerHTML = tilesize.value;
      return redraw(event);
    });
  };

  window.addEventListener('load', init);

}).call(this);
