export BERT_BASE_DIR=./uncased_L-12_H-768_A-12
export SQUAD_DIR=./datasets/SQuAD1.1

# python run_squad.py \
#   --vocab_file=$BERT_BASE_DIR/vocab.txt \
#   --bert_config_file=$BERT_BASE_DIR/bert_config.json \
#   --init_checkpoint=$BERT_BASE_DIR/bert_model.ckpt \
#   --do_train=True \
#   --train_file=$SQUAD_DIR/train-v1.1.json \
#   --do_predict=True \
#   --predict_file=$SQUAD_DIR/dev-v1.1.json \
#   --train_batch_size=12 \
#   --learning_rate=3e-5 \
#   --num_train_epochs=2.0 \
#   --max_seq_length=128 \
#   --doc_stride=64 \
#   --output_dir=./weights
python run_squad.py \
  --vocab_file=$BERT_BASE_DIR/vocab.txt \
  --bert_config_file=$BERT_BASE_DIR/bert_config.json \
  --init_checkpoint=./weights/model.ckpt-21899 \
  --do_train=False \
  --train_file=$SQUAD_DIR/train-v1.1.json \
  --do_predict=True \
  --predict_file=$SQUAD_DIR/s.json \
  --train_batch_size=12 \
  --learning_rate=3e-5 \
  --num_train_epochs=2.0 \
  --max_seq_length=128 \
  --doc_stride=64 \
  --output_dir=./output
