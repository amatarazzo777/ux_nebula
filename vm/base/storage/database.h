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

SQL, and tasDA. SQL processing. Remote. Already written materials.
Transfer local database to remove, leave file, keep cache.
Integrate with loarger database of different type.
Later sync. Every x sync.

Used and adapts to size. Memory databases to scale remote and local.


A person writing one would consider that the visitation of node map
of the trees, as a unit stored on disk and the edit commands are 
also suitable for network. Using a file and types of locking a certain
size of file can be accomidated. Supporting advanced searches

along with index data gathered from blob indexing (videos, images, texts, books)

The blocking mechanism provides for adjusting the components of a larger database when it
is broken up. Simply records tell the segment starts and stops. Indexing files can
use this and operate on a parrelle fasion. Adding advanced node storage is versitle,
however providing for a stream and easy location system for syntax is also nice.
Being able to store vectors of structures. 


Template parampack parameters <...> can be used in conjunction with type to for types of 
record scemea, as is the type of conception format. The storage of nodes, and variable amodes
of children. Some problems to solve, but should be a fun project.

Simply placing a marker file, and uploading this file to a server program will allow format reading.
Security is a concept not made here, typically user security. Or over encryption.



For a database link, it is a information part that can be easily updated. It also contains links to 
server addresses, will develop the connectivity for legacy formats, or` other file database formats.
odbc, jdbc. The database link here is also used for access to image data that was gather from news 
feeds for example. Video links. and provide a display format for the cached new xml feed.
Google XML search cache results from a data mining bot app running locally. Typically the file
system has multi user locking already built in. 

The database format can also be used for the desktop, and user application storage. The format works
better than many database competitiors. The update process from version to version is realitively 
quick when a programmer changes the data storage format or types of data. Importing can be done once,
or when needed. Most times done once is fine. Well planned applications update not as often. The
contact and email list. The listing of programs installed on the computer will use this data
base storage. 

as a system database, used by the operating system, perhaps networking will not be built in
to the library, the great dreams of SQL, and syncing left for the application
style database that inheirits this model. 

The database may be adopted for the object name database, and internal system usage. Therefore
making the usage, for structure storage, objects and also searching, function visitation 
can reduce code on usage and also specialize systems to invoke streams of this nature. That 
is as a remapping data target, from storage to memory, document object models can be saved
in the format. Providing for a streaming service.

The desktop can use this facility for memory of programs, desktop settings, visual rendering settings,
known wifi signals, etc. So the tempation is to create a system that is larger. Perhaps minimizing
the usage to templates provides the most effective storage means. Error free when the 
database engine can perform single user works. In memory. mutex can offer record locking for multiple
processes.

The facilities available as an inline algorithm in various languages can be a wonderful task.
Making the data storage contain only data, while indicies are stored in another area. 


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


class database_file_t {
public:
  struct header {
    static float version = 1.1;
    std::size_t free_storage;
  };

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
