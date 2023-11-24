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
*/

template <typename T> 
    class database_file_t {

    class data_node_t {
        T *node;

        std::size_t get_data_size() {
            if(constexpr std::is_base_of<std::basic_string, T>::value) {
                return node.size();
            } else if(constexpr std::is_base_of<std::vector, T>::value) {
                    return n.count() * n.get_data_size();
                } // invoke recusion on data_node_t class types
                
            }

            // if nodes contain compound types such as vectors of
            return sizeof(T);

        }
    };

    std::list<std::list<T>> node_list_t> data;
    void connect(std::string cs) = 0;
    void disconnect() = 0;

    // has the position on disk realive to a marker. The match tuple structure can contain extended information. 
    // The edits buffer contains valuable time saving buffer edit connands. Network reduction
    // only sending the changes to the monster 300 page novel, fifteen pages deletes, two words, paragraphs, move,  etc, words
    // and additional pages. 
    void update(uint_32_t tuple, unsigned char *edits, std::size_t size);
    void start_transaction();
    void end_transaction();
    void bail_transactions();
    void commit();


}
