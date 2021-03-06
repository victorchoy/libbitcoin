#ifndef LIBBITCOIN_STORAGE_POSTGRESQL_STORAGE_H
#define LIBBITCOIN_STORAGE_POSTGRESQL_STORAGE_H

#include <bitcoin/storage/storage.hpp>

#include <cppdb/frontend.h>
#include <string>
#include <mutex>

#include <bitcoin/util/threaded_service.hpp>

namespace libbitcoin {

class postgresql_blockchain;
typedef shared_ptr<postgresql_blockchain> postgresql_blockchain_ptr;

class postgresql_storage
  : public storage,
    public threaded_service,
    public std::enable_shared_from_this<postgresql_storage>
{
public:
    postgresql_storage(std::string database, 
            std::string user, std::string password);

    void store(const message::inv& inv, store_handler handle_store);
    void store(const message::transaction& transaction,
            store_handler handle_store);
    void store(const message::block& block, store_handler handle_store);

    void fetch_inventories(fetch_handler_inventories handle_fetch);
    void fetch_block_by_depth(size_t block_number, 
            fetch_handler_block handle_fetch);
    void fetch_block_by_hash(hash_digest block_hash, 
            fetch_handler_block handle_fetch);
    void fetch_block_locator(fetch_handler_block_locator handle_fetch);
    void fetch_output_by_hash(hash_digest transaction_hash, uint32_t index,
            fetch_handler_output handle_fetch);

    void block_exists_by_hash(hash_digest block_hash,
            exists_handler handle_exists);

private:
    void do_store_inv(const message::inv& inv, store_handler handle_store);
    void do_store_transaction(const message::transaction& transaction, 
            store_handler handle_store);
    void do_store_block(const message::block& block,
            store_handler handle_store);

    void do_fetch_inventories(fetch_handler_inventories handle_fetch);
    void do_fetch_block_by_depth(size_t block_number, 
            fetch_handler_block handle_fetch);
    void do_fetch_block_by_hash(hash_digest block_hash, 
            fetch_handler_block handle_fetch);
    void do_fetch_block_locator(fetch_handler_block_locator handle_fetch);
    void do_fetch_output_by_hash(hash_digest transaction_hash, uint32_t index,
            fetch_handler_output handle_fetch);

    void do_block_exists_by_hash(hash_digest block_hash,
            exists_handler handle_exists);

    // ------------

    void insert(operation oper, size_t script_id);
    size_t insert_script(operation_stack operations);
    void insert(const message::transaction_input& input,
            size_t transaction_id, size_t index_in_parent);
    void insert(const message::transaction_output& output,
            size_t transaction_id, size_t index_in_parent);
    size_t insert(const message::transaction& transaction);

    postgresql_blockchain_ptr blockchain_;
    cppdb::session sql_;
};

} // libbitcoin

#endif

