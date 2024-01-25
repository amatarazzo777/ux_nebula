/*
 * This file is part of the ux_nebula distribution
 * (https://github.com/amatarazzo777/ux_gui_stream).
 * Copyright (c) 2023 Anthony Matarazzo.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
Databases of a local nature, reserving the right to have a pointer
to records, a record or a field that is tracked perhaps. Node and
pointer storage database with memory allocation on reload. Index
building, partial index building. Record block saving.

*/

template <typename T>

class data_node_t {
  T *node;
  T *oldNode;

  std::size_t location;
  bool bchanged;
  uint32_t tuple;
  /* allows alias for non related application technology, same as pointer, in
   * scripting or database to screen linking by id, tuple may be appropiate.*/

  std::size_t get_data_size() {
    if (constexpr std::is_base_of<std::basic_string, T>::value) {
      return node.size();
    } else if (constexpr std::is_base_of<std::vector, T>::value) {
      // ways to use sum()
                    return sum(std::visit(node.get_data_size());
    }

    // if nodes contain compound types such as vectors of
    return sizeof(T);
  }

  // indexing function, used by the query engine for sorting.
  bool compare_greater(T *_rnode){return *node > _rnode};
  
};



class database_t {
  public:

  /*
   a specific index.  location by varying index operator. 
   objects into the system  can be hashed together to find any 
   type of index. Providing a remappable node list for any type 
   of indexes. As a format it can be a high level format for 
   types of standard template library. As well, encompassing 
   dynamic indexing, and searching, related nodes.

  */
  template typename<T, ...> operator[]::(T, ...) {

  };

  template operator<< {

  };

  template operator>> {

  };
 
};


/*
@brief When databases are stored on the disk, or network in a file,
these are the types of blocks the datastream can have.
The header is the first block in the file. The header
also points to the directory entri table. Where possibly
multiple objects exists. When data, index, directory, or
tuple space runs out because of editing, the chain block is used to
point to new informaiton written in freespace.*/
static class enum db_block_type {
  db_block_header,
  db_block_index,
  db_block_data,
  db_block_tuple,
  db_block_directory,
  db_block_chain
};

/*
The type of system database file. This information is in the database header.
The database file format replaces the application modules and also program
type from the standard linux api. The system functions start_process, and 
also fork, are wrapped with the database reader. The program reader
applies the same methods as the system api. Eventually the format readers 
should be included as part of the OS.

The db_object provides a non mangling namespace to identify prototypes
and interfaces by integer reference. Objects within the newer format 
can be applied to multiple languages and also container types. Essentually
the object operators, hashing mechanism, and a few other routines are utilized.
The prototypes and calling interface mechanism are described. 

The language object provides a standard mechanism for using compilers on the system. 
Languages can be dynamically built. The object file format encapsolates the 
cache and also other parts of the programming language. The object is 
tailored to work with an IDE, or multiple IDEs that can utilize the format, programs.
Source code, or compacted sealed source code, can be compiled.

the db_index, and db_data are for storage of object data within a node list.
The data may be read, while the structure is preserved on file as well 
as in memory. The formt provides an mechanism for query.

*/
static class enum system_db_type {
  db_program,
  db_object,
  db_language,
  db_index,
  db_data,
  db_document_tree,
  db_document_transform,
  db_directory,
  db_composite,
  db_font,
  db_brush,
  db_image,
  db_audio,
  db_scenegraph,
  db_video,
  db_shape,
  db_registry,
  db_symbolic_link

};


template<typename T> class database_file_t {
public:
  struct header {
    static float version = 1.0;
    system_db_type dbtype;
    std::size_t free_storage;
`  };

  class relative_chain_t {
  public:
    static const std::size_t stamp=0xff11;
    u_int32_t block;
    std::size_t position;
  };

  class relative_freespace_t {
  public:
    static const std::size_t stamp=0xff10;
    std::size_t length;
  };

  class edit {
  public:
    // visit for the nice record  edit of large texts, or parts of images,
    // blob data instruction edit of binary data. Font texture update because
    // of antialias smuge. the chain block, writes the signature and adds to free storage.
    //
    void visit(std::ostream _odbLock) {
      switch (editType) {
      case _tupleExpand:
        // write chain record and update free storage space with the in space
        // connected. some types of data will expand and leave the orginal
        // black. This occurs when the space on disk for the oringal data of the variable length
        // blob (string, array data), that at the point inside where it is compacted, 
        //or at the beginning making the entire block a hole. chain does this and updates
        // the header. If this does no
        chain(_odbLock, e);
      // clears a space usually at the end due to a delete, data residue.
      // the space is not acually cleared, but tagged as removed. 
      case _tupleClear:
        _odbLock.fseek(relative, e->location);
        _odbLock << relative_freespace_t{e.size()};

      case _tupleWrite:
        _odbLock.fseek(relative, e->location);
        _odbLock.fwrite(e.data(), e.size());
      }
    }
  };
  std::list<std::list<std::uniqur_ptr<T>>> node_list_t > data;
  std::list<std::uniqur_ptr<T>> changed;

  void connect(std::string cs) = 0;
  void disconnect() = 0;

  // has the position on disk realive to a marker. The match tuple structure can
  // contain extended information. The edits buffer contains valuable time
  // saving buffer edit connands. Network reduction only sending the changes to
  // the monster 300 page novel, fifteen pages deletes, two words, paragraphs,
  // move,  etc, words and additional pages.
  void update(uint_32_t tuple, unsigned char *edits, std::size_t size);

  void commit() {
    if(t!=0)
        std::throw("invalid nesting of transactions.");
    for_each(n : changed) {
      odb.fseek(absolute, n->location);
      if (b->bedit)
        std::visit(odb, n->edits);
      else {
        // new record, insert record, or update not needing edits just over
        // writes, changed numbers, etc.
        odb.fseek(n->location());
        odb.fwrite(n->data(), n->size());
      }
    }
    odb.flush();
  };
};
}
